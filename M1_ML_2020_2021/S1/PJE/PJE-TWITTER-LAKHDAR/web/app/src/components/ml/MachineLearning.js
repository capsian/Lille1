import React, {Component} from 'react'

const axios = require('axios')


export default class MachineLearning extends Component {

    constructor(props) {
        super(props);

        this.state = {
            campaignCSVFiles: [],
            trainingCSVFiles: [],
            testCSVFiles: [],
        }
    }

    handleCSVFiles() {
        let data = {"path": ""}
        axios.post('http://localhost:5000/csv/files', data)
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
                                <h5 className="card-title">Machine Learning</h5>
                                <div className="row">
                                    <div className="col-10">
                                        <div className="card">
                                            <div className="card-body">
                                                <h5 className="card-title">Tweet Cleaner</h5>
                                            </div>
                                        </div>
                                    </div>
                                </div>
                            </div>
                        </div>
                    </div>
                </div>
            </div>
        )
    }
}