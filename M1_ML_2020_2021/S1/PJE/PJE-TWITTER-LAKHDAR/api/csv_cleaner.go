package api

import (
	"encoding/json"
	"github.com/rs/zerolog/log"
	"gitlab-etu.fil.univ-lille1.fr/lakhdar/PJE-TWITTER-LAKHDAR/internal"
	"net/http"
)

const tweetParserFile = "scripts/ml/tweet_parser.py"
const dataDir = "data/campaign/"

type CSVCleanerReq struct {
	CSVFile string `json:"csvFile"`
}

type CSVCleanerRsp struct {
	Request CSVCleanerReq    `json:"request"`
	Tweets  []internal.Tweet `json:"tweets"`
}

// Handling /csv/clean POST request
func CSVCleanerHandler(w http.ResponseWriter, r *http.Request) {
	var csvReq CSVCleanerReq
	err := json.NewDecoder(r.Body).Decode(&csvReq)
	if err != nil {
		log.Error().Err(err).Msg("unmarshall /csv/cleaner error")
		return
	}

	if len(csvReq.CSVFile) == 0 {
		log.Error().Msgf("/csv/cleaner empty query !")
		return
	}
	log.Info().Msgf("/csv/cleaner: %s", csvReq.CSVFile)

	// format the return
	var out CSVCleanerRsp
	out.Request = csvReq

	exitCode := internal.ScriptRunner(tweetParserFile, "-c", dataDir+csvReq.CSVFile)
	if string(exitCode) != "1" {
		log.Error().Msgf("exitCode: %s, error while exec clean of: %s", exitCode, dataDir+csvReq.CSVFile)
	} else {
		out.Tweets = internal.ReadCSV(dataDir + csvReq.CSVFile)
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
