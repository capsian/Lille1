package main

import (
	"github.com/rs/zerolog/log"
	"gitlab-etu.fil.univ-lille1.fr/lakhdar/PJE-TWITTER-LAKHDAR/internal"
)


func main() {
	res := internal.ScriptRunner("/home/alpha/go/src/gitlab-etu.fil.univ-lille1.fr/lakhdar/PJE-TWITTER-LAKHDAR/scripts/ml/tweet_parser.py")
	log.Info().Interface("res", res).Msg("??")
}
