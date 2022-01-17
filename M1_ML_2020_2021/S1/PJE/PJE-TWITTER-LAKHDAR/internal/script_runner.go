package internal

import (
	"github.com/rs/zerolog/log"
	"os/exec"
	"strings"
)

const CMDName = "python"

func ScriptRunner(arg ...string) string {

	cmd := exec.Command(CMDName, arg...)
	out, err := cmd.Output()
	if err != nil {
		log.Error().Err(err).Msgf("error while exec: %s args:%s", CMDName, arg)
		log.Error().Msgf("output: %s", out)
		return ""
	}
	log.Info().Msgf("ScriptRunner: %s", out)
	return strings.TrimSuffix(string(out), "\n")
}
