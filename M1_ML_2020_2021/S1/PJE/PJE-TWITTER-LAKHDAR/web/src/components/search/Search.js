import React from "react";
import TweetList from "../tweet-list/TweetList";

const axios = require('axios')

export default class Search extends React.Component {
    constructor(props) {
        super(props)
        this.state = {
            searchQuery: "Hello",
            stream: false,
        }

        this.handleSubmit = this.handleSubmit.bind(this);
        this.handleStreamChange = this.handleStreamChange.bind(this);
        this.handleSearchQueryChange = this.handleSearchQueryChange.bind(this);
    }

    handleSearchQueryChange(e) {
        e.preventDefault();
        console.log(e.target.value)
        this.setState({
            searchQuery: e.target.value
        })
    }

    handleStreamChange(e) {
        e.preventDefault();
        this.setState({
            stream: e.target.checked
        })
    }

    handleSubmit(e) {
        e.preventDefault();
        if (this.state.searchQuery.length === 0) {
            return;
        }

        console.log("searchQuery: " + this.state.searchQuery + ", stream:" + this.state.stream)
        const data = {
            "query": this.state.searchQuery.toString(),
            "stream": this.state.stream.toString()
        }

        axios({
            method: 'post',
            headers: {
                'Access-Control-Allow-Origin': '*',
                'Accept': 'application/json',
                'Content-Type': 'application/json',
            },
            url: 'http://localhost:5000/search',
            mode: 'no-cors',
            data: data
        })
            .then((response) => {
                this.props.onChange(response.data.tweets)
            })
            .catch(function (error) {
                console.log(error);
            });
    }

    render() {
        return (
            <div id="content">
                <div className="row">
                    <div className="col">
                        <div className="card">
                            <div className="card-body">
                                <h5 className="card-title">Search</h5>
                                <form onSubmit={this.handleSubmit} className="input-group">
                                    <div className="col">
                                        <input name="searchQuery" value={this.state.searchQuery}
                                               className="form-control"
                                               onChange={this.handleSearchQueryChange} type="text"/>
                                    </div>
                                    <div className="col">
                                        <label>Stream <input type="checkbox" name="stream" value={this.state.stream}
                                                             className="form-control"
                                                             onChange={this.handleStreamChange}/></label>
                                    </div>
                                    <div className="col">
                                        <input type="submit" className="form-control btn btn-primary"
                                               value="Search"/>
                                    </div>
                                </form>
                            </div>
                        </div>
                    </div>
                </div>
                <div className="row">
                    <div className="col">
                        <TweetList tweetList={this.props.tweetList} onChange={this.props.onChange}/>
                    </div>
                </div>
            </div>
        )
    }
}