package internal

import (
	"encoding/csv"
	"github.com/rs/zerolog/log"
	"io/ioutil"
	"os"
	"strconv"
)

const CSVDir = "data/campaign/"

func TweetsToCSV(tweets []Tweet, req string) {

	csvName := req + ".csv"
	csvPath := CSVDir + csvName
	init := true

	if fileExists(csvPath) {
		init = false
	}

	f, e := os.OpenFile(csvPath, os.O_APPEND|os.O_WRONLY|os.O_CREATE, 0644)
	if e != nil {
		log.Error().Err(e).Msgf("error while Open " + csvName)
		return
	}
	defer f.Close()

	csvWriter := csv.NewWriter(f)

	if init {
		header := []string{"ID", "REQ", "AUTHOR", "DATE", "LANG", "MSG", "SCORE"}
		if err := csvWriter.Write(header); err != nil {
			log.Error().Err(err).Msgf("error writing header")
			return
		}
	}

	for i, elem := range tweets {
		record := []string{
			elem.ID,
			req,
			elem.Author,
			elem.CreatedAt,
			elem.Lang,
			elem.Message,
			strconv.Itoa(elem.Score),
		}
		if err := csvWriter.Write(record); err != nil {
			log.Error().Err(err).Msgf("error writing record to csv: %d", i)
		}
	}

	csvWriter.Flush()

	if err := csvWriter.Error(); err != nil {
		log.Error().Err(err).Msgf("error after flush")
	}
}

func fileExists(filename string) bool {
	info, err := os.Stat(filename)
	if os.IsNotExist(err) {
		return false
	}
	return !info.IsDir()
}

func ReadCSV(csvPath string) []Tweet {
	var out []Tweet

	file, err := os.Open(csvPath)
	if err != nil {
		log.Error().Err(err).Msgf("error while reading file %s", csvPath)
		return out
	}
	defer file.Close()

	reader := csv.NewReader(file)

	records, err := reader.ReadAll()
	if err != nil {
		log.Error().Err(err).Msgf("error while reading records of %s", csvPath)
		return out
	}

	for _, t := range records {
		score, _ := strconv.Atoi(t[6])
		out = append(out, Tweet{
			ID:        t[0],
			Request:   t[1],
			Author:    t[2],
			CreatedAt: t[3],
			Lang:      t[4],
			Message:   t[5],
			Score:     score,
		})
	}

	return out
}

func GetCSVFiles(path string) []string {
	files, err := ioutil.ReadDir(path)
	if err != nil {
		log.Error().Err(err).Msgf("error while reading files of %s", path)
		return nil
	}

	var files_name []string
	for _, f := range files {
		files_name = append(files_name, f.Name())
	}

	return files_name
}
