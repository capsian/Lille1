import React from "react";

import Tweet from "../tweet/Tweet"

export default class TweetList extends React.Component {
    constructor(props) {
        super(props);
        this.state = {
            selected: []
        }

        this.handleSelected = this.handleSelected.bind(this);
    }

    handleSelected(e) {
        e.preventDefault();
        if (e.target.value.length === 0) {
            return
        }

        // no dup
        if (!this.state.selected.includes(e.target.value)) {
            console.log("Adding: " + e.target.value)
            this.setState({
                selected: this.state.selected.concat(e.target.value),
            })
            console.log(this.state.selected)
        }
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
                    <th>ReplyCount</th>
                    <th>RetweetCount</th>
                    <th>Country</th>
                    <th>Message</th>
                    <th>NbChars</th>
                    <th>Score</th>
                    <th>Select</th>
                </tr>
                </thead>
                <tbody>

                {this.props.tweetList.map(elem => (
                    <Tweet onChange={this.handleSelected}
                           id={elem.id}
                           createdAt={elem.createdAt}
                           author={elem.author}
                           lang={elem.lang}
                           replyCount={elem.replyCount}
                           retweetCount={elem.retweetCount}
                           country={elem.country}
                           message={elem.message}
                           nbChars={elem.nbChars}
                           score="0"
                           key={elem.id}
                    />
                ))}
                </tbody>
            </table>
        );
    }
}