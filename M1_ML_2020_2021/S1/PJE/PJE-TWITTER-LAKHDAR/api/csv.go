package api

import (
	"encoding/json"
	"github.com/rs/zerolog/log"
	"gitlab-etu.fil.univ-lille1.fr/lakhdar/PJE-TWITTER-LAKHDAR/internal"
	"io/ioutil"
	"net/http"
)

type CSVRequest struct {
	CSVFile string `json:"csvFile"`
}

type CSVRequestRsp struct {
	Request CSVRequest       `json:"request"`
	Tweets  []internal.Tweet `json:"tweets"`
}

// Handling /csv GET request
func CSVHandler(w http.ResponseWriter, r *http.Request) {
	var csvReq SearchRequest
	err := json.NewDecoder(r.Body).Decode(&csvReq)
	if err != nil {
		log.Error().Err(err).Msg("unmarshall SearchRequest error")
		return
	}

	if len(csvReq.Query) == 0 {
		log.Error().Msgf("/csv empty query !")
		return
	}
	log.Info().Msgf("csvReq: %s", csvReq.Query)

	// format the return
	var out SearchRequestRsp

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

type CSVFilesRequest struct {
	Path string `json:"path"`
}

type CSVFilesRequestRsp struct {
	Files []string       `json:"files"`
}

// Handling /csv_files GET request
func CSVFilesHandler(w http.ResponseWriter, r *http.Request) {
	var csvFilesReq CSVFilesRequest
	err := json.NewDecoder(r.Body).Decode(&csvFilesReq)
	if err != nil {
		log.Error().Err(err).Msg("unmarshall CSVFilesHandler error")
		return
	}

	if len(csvFilesReq.Path) == 0 {
		log.Error().Msgf("/csv/files empty query !")
		return
	}
	log.Info().Msgf("csvFilesReq: %s", csvFilesReq.Path)

	// format the return
	var out CSVFilesRequestRsp
	files, err := ioutil.ReadDir("/home/alpha/go/src/gitlab-etu.fil.univ-lille1.fr/lakhdar/PJE-TWITTER-LAKHDAR/data/" + csvFilesReq.Path)
	if err != nil {
		log.Error().Err(err).Msg("read dir error")
		return
	}

	for _, f := range files {
		out.Files = append(out.Files, f.Name())
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