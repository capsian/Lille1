package api

import (
	"encoding/json"
	"github.com/rs/zerolog/log"
	"gitlab-etu.fil.univ-lille1.fr/lakhdar/PJE-TWITTER-LAKHDAR/internal"
	"net/http"
)

type SearchRequest struct {
	Query   string `json:"query"`
	English string `json:"english"`
}

type SearchRequestRsp struct {
	Request SearchRequest    `json:"request"`
	Tweets  []internal.Tweet `json:"tweets"`
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
	log.Info().Msgf("SearchRequest: %s, english:%s", sr.Query, sr.English)

	if sr.English == "false" {
		sr.English = ""
	} else {
		sr.English = "en"
	}

	tc := internal.InitClient()
	res, err := tc.Search(sr.Query, sr.English)
	if err != nil {
		log.Error().Err(err).Msg("twitter search error")
		return
	}

	// format the return
	var out SearchRequestRsp
	out.Request = sr
	for _, elem := range res.Statuses {
		out.Tweets = append(out.Tweets, internal.Tweet{
			ID:        elem.IDStr,
			Request:   sr.Query,
			CreatedAt: elem.CreatedAt,
			Author:    elem.User.Name,
			Lang:      elem.Lang,
			Message:   elem.Text,
			Score:     -1,
		})
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

	// write to CSV
	internal.TweetsToCSV(out.Tweets, out.Request.Query)
}
