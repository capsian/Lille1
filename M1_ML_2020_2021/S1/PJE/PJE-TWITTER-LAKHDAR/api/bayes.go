package api

import (
	"encoding/json"
	"github.com/rs/zerolog/log"
	"gitlab-etu.fil.univ-lille1.fr/lakhdar/PJE-TWITTER-LAKHDAR/internal"
	"net/http"
)

const BayesScript = "scripts/ml/tweet_classifier_bayes.py"


type BayesReq struct {
	Tweet string `json:"tweet"`
	Mode  string `json:"mode"`
	Grams string `json:"grams"`
}

type BayesResp struct {
	Request BayesReq `json:"request"`
	Score   int      `json:"score"`
}

// Handling /search POST request
func BayesHandler(w http.ResponseWriter, r *http.Request) {
	var br BayesReq
	err := json.NewDecoder(r.Body).Decode(&br)
	if err != nil {
		log.Error().Err(err).Msg("unmarshall BayesHandler error")
		return
	}

	if (len(br.Tweet) == 0) && (len(br.Mode) == 0) {
		log.Error().Msgf("/bayes empty query !")
		return
	}
	log.Info().Msgf("BayesReq: %s", br)

	out := internal.ScriptRunner(BayesScript, "-t", br.Tweet, "-m", br.Mode, "-g", br.Grams, "-min", "1")

	jsonResponse, jsonError := json.Marshal(out)
	if jsonError != nil {
		log.Error().Err(err).Msg("bayes response marshall error")
		return
	}

	w.Header().Set("Access-Control-Allow-Origin", "*")
	w.Header().Set("Content-Type", "application/json")
	w.WriteHeader(http.StatusOK)
	w.Write(jsonResponse)
}
