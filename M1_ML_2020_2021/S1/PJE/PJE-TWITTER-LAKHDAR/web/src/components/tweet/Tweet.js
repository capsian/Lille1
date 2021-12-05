import React from "react";

export default class Tweet extends React.Component {
    render() {
        return (
            <tr>
                <td> {this.props.id}</td>
                <td> {this.props.createdAt}</td>
                <td> {this.props.author}</td>
                <td> {this.props.lang}</td>
                <td> {this.props.replyCount}</td>
                <td> {this.props.retweetCount}</td>
                <td> {this.props.country}</td>
                <td> {this.props.message}</td>
                <td> {this.props.nbChars}</td>
                <td> {this.props.score}</td>
                <td><input type="checkbox" value={this.props.id} onChange={this.props.onChange}/></td>
            </tr>
        );
    }
}