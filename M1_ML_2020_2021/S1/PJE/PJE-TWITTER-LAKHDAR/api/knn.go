package api

import (
	"encoding/json"
	"github.com/rs/zerolog/log"
	"gitlab-etu.fil.univ-lille1.fr/lakhdar/PJE-TWITTER-LAKHDAR/internal"
	"net/http"
)

const KNNScript = "scripts/ml/tweet_classifier_knn.py"

type KNNReq struct {
	Tweet     string `json:"tweet"`
	Grams     string `json:"grams"`
	Neighbors string `json:"neighbors"`
	DistFunc  string `json:"distFunc"`
}

type KNNResp struct {
	Request KNNReq `json:"request"`
	Score   int    `json:"score"`
}

// Handling /search POST request
func KNNHandler(w http.ResponseWriter, r *http.Request) {
	var knnR KNNReq
	err := json.NewDecoder(r.Body).Decode(&knnR)
	if err != nil {
		log.Error().Err(err).Msg("unmarshall KNNHandler error")
		return
	}

	if (len(knnR.Tweet) == 0) && (len(knnR.Grams) == 0) && (len(knnR.Neighbors) == 0) && (len(knnR.DistFunc) == 0)  {
		log.Error().Msgf("/knn empty query !")
		return
	}
	log.Info().Msgf("/knn: %s", knnR)

	out := internal.ScriptRunner(KNNScript, "-k", knnR.Neighbors, "-d", knnR.DistFunc, "-t", knnR.Tweet)

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
