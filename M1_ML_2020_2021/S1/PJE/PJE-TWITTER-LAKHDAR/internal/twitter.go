package internal

import (
	"github.com/dghubble/go-twitter/twitter"
	"github.com/dghubble/oauth1"
)

type Tweet struct {
	ID        string `json:"id"`
	Request   string `json:"request"`
	Author    string `json:"author"`
	CreatedAt string `json:"createdAt"`
	Lang      string `json:"lang"`
	Message   string `json:"message"`
	Score     int    `json:"score"`
}

type TwitterClient struct {
	client         *twitter.Client
	stream         *twitter.StreamService
	consumerKey    string
	consumerSecret string
	token          string
	tokenSecret    string
}

func InitClient() TwitterClient {
	var c TwitterClient
	config := oauth1.NewConfig("", "")
	token := oauth1.NewToken("", "")
	// http.Client will automatically authorize Requests
	httpClient := config.Client(oauth1.NoContext, token)
	// Twitter client
	c.client = twitter.NewClient(httpClient)
	return c
}

func (tc TwitterClient) Search(query string, english string) (*twitter.Search, error) {
	search, _, err := tc.client.Search.Tweets(&twitter.SearchTweetParams{
		Query: query,
		Lang: english,
	})
	if err != nil {
		return nil, err
	}
	return search, nil
}
