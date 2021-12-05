package internal

import (
	"github.com/dghubble/go-twitter/twitter"
	"github.com/dghubble/oauth1"
	"os"
	"os/signal"
	"syscall"
)

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
	config := oauth1.NewConfig("z6HLTHCzCPw0U1RmftFuvTAIy", "LMzefF7UachGAd9ZpGBinA6bdIpBufaREY1SY7bgNycNlI1O2o")
	token := oauth1.NewToken("2170823953-YjTkqlGbFKNtplZutivKjGVjTx3UcWGRb5jGRec", "OF50AgKkmgl5mqow4rW9q6a1JcvzSkR0u3GruIeUe15pX")
	// http.Client will automatically authorize Requests
	httpClient := config.Client(oauth1.NoContext, token)
	// Twitter client
	c.client = twitter.NewClient(httpClient)
	return c
}

func (tc TwitterClient) Search(query string) (*twitter.Search, error) {
	search, _, err := tc.client.Search.Tweets(&twitter.SearchTweetParams{
		Query: query,
	})
	if err != nil {
		return nil, err
	}
	return search, nil
}

func (tc TwitterClient) Stream(query string) (*twitter.Search, error) {

	// Convenience Demux demultiplexed stream messages
	demux := twitter.NewSwitchDemux()
	demux.Tweet = func(tweet *twitter.Tweet) {
		//fmt.Println(tweet.Text)
	}
	demux.DM = func(dm *twitter.DirectMessage) {
		//fmt.Println(dm.SenderID)
	}
	demux.Event = func(event *twitter.Event) {
		//fmt.Printf("%#v\n", event)
	}

	//fmt.Println("Starting Stream...")

	// FILTER
	filterParams := &twitter.StreamFilterParams{
		Track:         []string{"cat"},
		StallWarnings: twitter.Bool(true),
	}
	stream, err := tc.stream.Filter(filterParams)
	if err != nil {
		//log.Fatal(err)
	}

	go demux.HandleChan(stream.Messages)

	// Wait for SIGINT and SIGTERM (HIT CTRL-C)
	ch := make(chan os.Signal)
	signal.Notify(ch, syscall.SIGINT, syscall.SIGTERM)
	//log.Println(<-ch)

	//fmt.Println("Stopping Stream...")
	stream.Stop()

	return nil, nil
}
