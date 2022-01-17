package main

import (
	"github.com/rs/zerolog/log"
	"gitlab-etu.fil.univ-lille1.fr/lakhdar/PJE-TWITTER-LAKHDAR/api"
	"net/http"
	"os"
	"path/filepath"
)

var staticPath string

func init() {
	var err error
	log.Info().Msgf("== Init ==")
	log.Info().Msgf("Setting up server on 127.0.0.1:5000")
	log.Info().Msgf("Author: Lakhdar Selim <selim.lakhdar[[@]]gmail.com>")
	staticPath, err = filepath.Abs(filepath.Dir(os.Args[0]))
	if err != nil {
		log.Fatal().Err(err).Msgf("unable to get static path")
	}
	staticPath = filepath.Dir(staticPath) + "/app/build/web"

	log.Info().Msgf("Serving from %s", staticPath)
	log.Info().Msgf("== Server On ==")
}

func main() {
	http.Handle("/", http.FileServer(http.Dir(staticPath)))
	http.HandleFunc("/search", api.SearchHandler)
	http.HandleFunc("/csv/files", api.CSVFilesHandler)
	http.HandleFunc("/csv/cleaner", api.CSVCleanerHandler)
	http.HandleFunc("/bayes", api.BayesHandler)
	http.HandleFunc("/keyword", api.KeywordHandler)
	http.HandleFunc("/knn", api.KNNHandler)
	http.ListenAndServe(":5000", nil)
}
