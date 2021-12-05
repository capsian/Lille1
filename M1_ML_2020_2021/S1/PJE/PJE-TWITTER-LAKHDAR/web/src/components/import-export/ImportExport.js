import React, {Component} from 'react'

import {CSVReader} from 'react-papaparse'
import TweetList from "../tweet-list/TweetList";

const buttonRef = React.createRef()

export default class ImportExport extends Component {

    handleOpenDialog = (e) => {
        // Note that the ref is set async, so it might be null at some point
        if (buttonRef.current) {
            buttonRef.current.open(e)
        }
    }

    handleOnFileLoad = (data) => {
        let header = true
        let out = []
        for (let elem of data) {
            if (header) {
                header = false;
                continue
            }
            let tmp = {
                id: elem.data[0],
                createdAt: elem.data[1],
                author: elem.data[2],
                lang: elem.data[3],
                replyCount: elem.data[4],
                retweetCount: elem.data[5],
                country: elem.data[6],
                message: elem.data[7],
                nbChars: elem.data[8],
                score: elem.data[9],
            }
            out = out.concat(tmp)
        }

        this.props.onChange(out)
    }

    handleOnError = (err, file, inputElem, reason) => {
        console.log(err)
    }

    render() {
        return (
            <div id="content">
                <div className="row">
                    <div className="col">
                        <div className="card">
                            <div className="card-body">
                                <h5 className="card-title">Import</h5>
                                <CSVReader
                                    ref={buttonRef}
                                    onFileLoad={this.handleOnFileLoad}
                                    onError={this.handleOnError}
                                    noClick
                                    noDrag
                                >
                                    {({file}) => (
                                        <aside>
                                            <button className="btn btn-primary" onClick={this.handleOpenDialog}>
                                                Browse file
                                            </button>
                                            <div>
                                                {file && file.name}
                                            </div>
                                        </aside>
                                    )}
                                </CSVReader>
                            </div>
                        </div>
                    </div>
                </div>
                <div className="row">
                    <div className="col">
                        <div className="card">
                            <div className="card-body">
                                <h5 className="card-title">Export</h5>
                                <TweetList tweetList={this.props.tweetList} onChange={this.props.onChange}/>
                            </div>
                        </div>
                    </div>
                </div>
            </div>
        )
    }
}