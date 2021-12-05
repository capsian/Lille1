package api


import (
	"encoding/json"
	"github.com/rs/zerolog/log"
	"gitlab-etu.fil.univ-lille1.fr/lakhdar/PJE-TWITTER-LAKHDAR/internal"
	"io/ioutil"
	"net/http"
	"strings"
)

type Tweet struct {
	ID           string `json:"id"`
	Author       string `json:"author"`
	CreatedAt    string `json:"createdAt"`
	Lang         string `json:"lang"`
	ReplyCount   int    `json:"replyCount"`
	RetweetCount int    `json:"retweetCount"`
	Country      string `json:"country"`
	Message      string `json:"message"`
	NbChars      int    `json:"nbChars"`
}

type SearchRequest struct {
	Query  string `json:"query"`
	Stream string `json:"stream"`
}

type SearchRequestRsp struct {
	Request SearchRequest `json:"request"`
	Tweets  []Tweet       `json:"tweets"`
}

// Handling /stream POST request
func StreamHandler(w http.ResponseWriter, r *http.Request) {
	body, err := ioutil.ReadAll(r.Body)
	if err != nil {
		log.Error().Err(err).Msg("read body error")
		return
	}

	var sr SearchRequest
	err = json.Unmarshal(body, &sr)
	if err != nil {
		log.Error().Err(err).Msg("unmarshall SearchRequest error")
		return
	}
}

// Handling /search POST request
func SearchHandler(w http.ResponseWriter, r *http.Request) {
	var sr SearchRequest
	err := json.NewDecoder(r.Body).Decode(&sr)
	if err != nil {
		log.Error().Err(err).Msg("unmarshall SearchRequest error")
		return
	}

	if len(sr.Query) == 0 {
		log.Error().Msgf("/search empty query !")
		return
	}
	log.Info().Msgf("SearchRequest: %s, Stream:%s", sr.Query, sr.Stream)

	tc := internal.InitClient()
	res, err := tc.Search(sr.Query)
	if err != nil {
		log.Error().Err(err).Msg("twitter search error")
		return
	}

	// format the return
	var out SearchRequestRsp
	out.Request = sr
	for i, elem := range res.Statuses {
		out.Tweets = append(out.Tweets, Tweet{
			ID:           elem.IDStr,
			Author:       elem.User.Name,
			CreatedAt:    elem.CreatedAt,
			Lang:         elem.Lang,
			ReplyCount:   elem.ReplyCount,
			RetweetCount: elem.RetweetCount,
			Message:      elem.Text,
			NbChars:      len(strings.TrimSpace(elem.Text)),
		})
		if elem.Place != nil {
			out.Tweets[i].Country = elem.Place.Country
		}
	}

	jsonResponse, jsonError := json.Marshal(out)
	if jsonError != nil {
		log.Error().Err(err).Msg("twitter response marshall error")
		return
	}

	w.Header().Set("Access-Control-Allow-Origin", "*")
	w.Header().Set("Content-Type", "application/json")
	w.WriteHeader(http.StatusOK)
	w.Write(jsonResponse)
}

