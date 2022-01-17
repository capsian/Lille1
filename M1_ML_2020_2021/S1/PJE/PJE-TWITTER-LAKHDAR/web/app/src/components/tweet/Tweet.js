import React from "react";

const axios = require('axios')

export default class Tweet extends React.Component {

    constructor(props) {
        super(props);
        this.state = {
            classifier: "keyword",
            grams: "1",
            neighbors: "1",
            distFunc: "dist_simple",
            score: "-1"
        }

        this.handleSubmitScoring = this.handleSubmitScoring.bind(this);
        this.handleClassifier = this.handleClassifier.bind(this);
        this.handleGram = this.handleGram.bind(this);
        this.handleNeighbors = this.handleNeighbors.bind(this);
        this.handleDistFunc = this.handleDistFunc.bind(this);
        this.handleSubmitScoring = this.handleSubmitScoring.bind(this);
    }

    handleClassifier(e) {
        e.preventDefault();
        this.setState({classifier: e.target.value});
    }

    handleGram(e) {
        e.preventDefault();
        this.setState({grams: e.target.value});
    }

    handleNeighbors(e) {
        e.preventDefault();
        this.setState({neighbors: e.target.value});
    }

    handleDistFunc(e) {
        e.preventDefault();
        this.setState({distFunc: e.target.value});
    }

    handleSubmitScoring(e) {
        e.preventDefault();
        let data = {
            "tweet": this.props.message
        }

        console.log("classify with: " + this.state.classifier)

        let apiTarget = "http://localhost:5000"

        if (this.state.classifier === "bayesFreq") {
            apiTarget += "/bayes"
            data.mode = "FREQUENCY"
            data.grams = this.state.grams
        }

        if (this.state.classifier === "bayesPres") {
            apiTarget += "/bayes"
            data.mode = "PRESENCE"
            data.grams = this.state.grams
        }

        if (this.state.classifier === "keyword") {
            apiTarget += "/keyword"
            data.grams = this.state.grams
        }

        if (this.state.classifier === "knn") {
            apiTarget += "/knn"
            data.distFunc = this.state.distFunc
            data.neighbors = this.state.neighbors
            data.grams = this.state.grams
        }

        console.log("classify with:")
        console.log(data)

        axios.post(apiTarget, data)
            .then((response) => {
                this.setState({
                        'score': response.data
                    }
                )
            })
            .catch(function (error) {
                console.log(error);
            });
    }

    render() {
        return (
            <tr>
                <td> {this.props.id}</td>
                <td> {this.props.createdAt}</td>
                <td> {this.props.author}</td>
                <td> {this.props.lang}</td>
                <td> {this.props.message}</td>
                <td> {this.props.score}</td>
                <td>
                    <button type="button" className="btn btn-info btn-lg" data-toggle="modal"
                            data-target="#myModal">Classification
                    </button>
                </td>
                <td>
                    <div id="myModal" className="modal fade" role="dialog">
                        <div className="modal-dialog modal-lg">
                            <div className="modal-content">
                                <div className="modal-header">
                                    <h4 className="modal-title">Classification</h4>
                                    <button type="button" className="close" data-dismiss="modal">&times;</button>
                                </div>
                                <div className="modal-body">
                                    <div className="row">
                                        <div className="col-12">
                                            <p>Tweet: {this.props.message}</p>
                                        </div>
                                    </div>
                                    <form onSubmit={this.handleSubmitScoring} className="input-group">
                                        <div className="row">
                                            <div className="col-3">
                                                <label htmlFor="classifier">Classifier</label>
                                                <select name="classifier" id="classifier"
                                                        onChange={this.handleClassifier}>
                                                    <option value="keyword">Keyword Counter</option>
                                                    <option value="knn">KNN</option>
                                                    <option value="bayesFreq">Bayes Freq</option>
                                                    <option value="bayesPres">Bayes Presence</option>
                                                </select>
                                            </div>
                                            <div className="col-3">
                                                <label htmlFor="ngram">N-gram</label>
                                                <select name="ngram" id="ngram" onChange={this.handleGram}>
                                                    <option value="1">1</option>
                                                    <option value="2">2</option>
                                                    <option value="3">3</option>
                                                    <option value="4">4</option>
                                                </select>
                                            </div>
                                            <div className="col-3">
                                                <label htmlFor="distFunc">Dist Function</label>
                                                <select name="distFunc" id="distFunc" onChange={this.handleDistFunc}>
                                                    <option value="dist_simple">dist_simple</option>
                                                    <option value="levenshtein">levenshtein</option>
                                                </select>
                                            </div>
                                            <div className="col-3">
                                                <label htmlFor="neighbors">Neighbors</label>
                                                <select name="neighbors" id="neighbors" onChange={this.handleNeighbors}>
                                                    <option value="1">1</option>
                                                    <option value="2">2</option>
                                                    <option value="3">3</option>
                                                    <option value="4">4</option>
                                                </select>
                                            </div>
                                        </div>
                                        <div className="row">
                                            <div className="col-4">
                                                <p>Score : {this.state.score}</p>
                                            </div>
                                            <div className="col-6">
                                                <input type="submit" className="btn btn-primary" value="Score"/>
                                            </div>
                                        </div>
                                    </form>

                                </div>
                                <div className="modal-footer">
                                    <button type="button" className="btn btn-default" data-dismiss="modal">Close
                                    </button>
                                </div>
                            </div>
                        </div>
                    </div>
                </td>
            </tr>
        );
    }
}