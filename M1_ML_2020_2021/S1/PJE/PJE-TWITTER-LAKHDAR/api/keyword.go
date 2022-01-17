package api

import (
	"encoding/json"
	"github.com/rs/zerolog/log"
	"gitlab-etu.fil.univ-lille1.fr/lakhdar/PJE-TWITTER-LAKHDAR/internal"
	"net/http"
)

const KeywordScript = "scripts/ml/tweet_classifier_keyword.py"

type KeywordReq struct {
	Tweet string `json:"tweet"`
	Grams string `json:"grams"`
}

type KeywordResp struct {
	Request KeywordReq `json:"request"`
	Score   int        `json:"score"`
}

// Handling /search POST request
func KeywordHandler(w http.ResponseWriter, r *http.Request) {
	var kr KeywordReq
	err := json.NewDecoder(r.Body).Decode(&kr)
	if err != nil {
		log.Error().Err(err).Msg("unmarshall KeywordHandler error")
		return
	}

	if (len(kr.Tweet) == 0) && (len(kr.Grams) == 0) {
		log.Error().Msgf("/keyword empty query !")
		return
	}
	log.Info().Msgf("KeywordReq: %s", kr)

	out := internal.ScriptRunner(KeywordScript, "-t", kr.Tweet, "-g", kr.Grams, "-min", "1")

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
