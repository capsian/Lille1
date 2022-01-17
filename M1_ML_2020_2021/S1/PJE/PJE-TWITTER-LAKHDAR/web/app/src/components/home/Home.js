import React, {Component} from 'react'

export default class Home extends Component {

    getCSVs() {

    }

    render() {
        return (
            <div id="content">
                <div className="row">
                    <div className="col">
                        <div className="card">
                            <div className="card-body">
                                <h5 className="card-title">Data</h5>
                                <div className="row">
                                    <div className="col-4">
                                        <div className="card">
                                            <div className="card-body">
                                                <h5 className="card-title">Running Campaign</h5>
                                            </div>
                                        </div>
                                    </div>
                                    <div className="col-4">
                                        <div className="card">
                                            <div className="card-body">
                                                <h5 className="card-title">Training Sets</h5>
                                            </div>
                                        </div>
                                    </div>
                                    <div className="col-4">
                                        <div className="card">
                                            <div className="card-body">
                                                <h5 className="card-title">Test Sets</h5>
                                            </div>
                                        </div>
                                    </div>
                                </div>
                            </div>
                        </div>
                    </div>
                </div>
                <div className="row">
                    <div className="col">
                        <div className="card">
                            <div className="card-body">
                                <h5 className="card-title">Stats</h5>
                                <div className="row">
                                    <div className="col-3">
                                        <div className="card">
                                            <div className="card-body">
                                                <h5 className="card-title">Totals</h5>
                                            </div>
                                        </div>
                                    </div>
                                    <div className="col-3">
                                        <div className="card">
                                            <div className="card-body">
                                                <h5 className="card-title">Positive Tweets</h5>
                                            </div>
                                        </div>
                                    </div>
                                    <div className="col-3">
                                        <div className="card">
                                            <div className="card-body">
                                                <h5 className="card-title">Negative Tweets</h5>
                                            </div>
                                        </div>
                                    </div>
                                    <div className="col-3">
                                        <div className="card">
                                            <div className="card-body">
                                                <h5 className="card-title">Neutral Tweets</h5>
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