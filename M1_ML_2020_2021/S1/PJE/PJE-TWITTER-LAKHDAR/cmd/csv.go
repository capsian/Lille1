package main

import (
	"github.com/rs/zerolog/log"
	"gitlab-etu.fil.univ-lille1.fr/lakhdar/PJE-TWITTER-LAKHDAR/internal"
)


func main() {
	files := internal.GetCSVFiles("/home/alpha/go/src/gitlab-etu.fil.univ-lille1.fr/lakhdar/PJE-TWITTER-LAKHDAR/data")
	log.Info().Msgf("%s", files)
}
