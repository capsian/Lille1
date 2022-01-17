import React from "react";

import Tweet from "../tweet/Tweet"

export default class TweetList extends React.Component {
    constructor(props) {
        super(props);
    }

    render() {
        return (
            <table className="table">
                <thead>
                <tr>
                    <th>#</th>
                    <th>CreatedAt</th>
                    <th>Author</th>
                    <th>Lang</th>
                    <th>Message</th>
                    <th>Score</th>
                    <th>Select</th>
                </tr>
                </thead>
                <tbody>
                {Object.keys(this.props.tweetSet).map((key) => (
                    <Tweet
                        key={this.props.tweetSet[key].id}
                        id={this.props.tweetSet[key].id}
                        createdAt={this.props.tweetSet[key].createdAt}
                        author={this.props.tweetSet[key].author}
                        lang={this.props.tweetSet[key].lang}
                        message={this.props.tweetSet[key].message}
                        score="-1"
                    />
                ))}
                </tbody>
            </table>
        );
    }
}