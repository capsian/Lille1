import React from 'react';
import {BrowserRouter as Router, Link, Route, Switch} from "react-router-dom";

import './App.css';

import Home from './components/home/Home'
import Search from './components/search/Search'
import ImportExport from "./components/import-export/ImportExport";
import MachineLearning from "./components/ml/MachineLearning";

class App extends React.Component {
    constructor(props) {
        super(props);
        this.state = {
            tweetList: [],
        }

        this.handleTweetListChange = this.handleTweetListChange.bind(this);
    }

    handleTweetListChange(tweets) {
        this.setState({
            tweetList: this.state.tweetList.concat(tweets)
        })
    }

    render() {
        return (
            <div className="container-fluid">
                <div id="header" className="row center">
                    <div className="col text-center"><h1>PJE - Twitter</h1></div>
                </div>
                <Router>
                    <div id="menu" className="row center m-4 primary">
                        <div className="col text-center"><Link to="/">
                            <button className="col btn btn-success">Home</button>
                        </Link></div>
                        <div className="col text-center"><Link to="/search">
                            <button className="col btn btn-success">Search</button>
                        </Link></div>
                        <div className="col text-center"><Link to="/import_export">
                            <button className="col btn btn-success">Import/Export</button>
                        </Link>
                        </div>
                        <div className="col text-center"><Link to="/ml">
                            <button className="col btn btn-success">ML</button>
                        </Link>
                        </div>
                    </div>
                    <Switch>

                        <Route path="/search">
                            <Search onChange={this.handleTweetListChange} tweetList={this.state.tweetList}/>
                        </Route>
                        <Route path="/import_export">
                            <ImportExport onChange={this.handleTweetListChange} tweetList={this.state.tweetList}/>
                        </Route>
                        <Route path="/ml">
                            <MachineLearning/>
                        </Route>
                        <Route path="/">
                            <Home/>
                        </Route>

                    </Switch>
                </Router>
                <div id="footer" className="row center m-4 ">
                    <div className="col text-center">Author: Selim Lakhdar</div>
                </div>
            </div>
        );
    }


}

export default App;
