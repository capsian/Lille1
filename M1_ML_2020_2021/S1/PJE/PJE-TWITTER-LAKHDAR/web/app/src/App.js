import React from 'react';
import {BrowserRouter as Router, Link, Route, Switch} from "react-router-dom";

import './App.css';

import Home from './components/home/Home'
import Search from './components/search/Search'
import MachineLearning from "./components/ml/MachineLearning";

class App extends React.Component {
    constructor(props) {
        super(props);
        this.state = {
            tweetSet: {},
        }

        this.handleTweetSetChange = this.handleTweetSetChange.bind(this);
    }

    handleTweetSetChange(tweets) {
        for (let tweet of tweets) {
            if (this.state.tweetSet[tweet.id] === undefined) {
                this.setState(() => {
                    this.state.tweetSet[tweet.id] = tweet
                    return {};
                })
            }
        }
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
                        <div className="col text-center"><Link to="/ml">
                            <button className="col btn btn-success">ML</button>
                        </Link>
                        </div>
                    </div>
                    <Switch>

                        <Route path="/search">
                            <Search onChange={this.handleTweetSetChange} tweetSet={this.state.tweetSet}/>
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
