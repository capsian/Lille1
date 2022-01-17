#!/usr/local/bin/python3

import argparse
import json

import numpy as np

import tweet_parser


class BayesClassifier:
    name = "BayesClassifier"
    x, y, scores = {}, {}, {}
    pos_words, neg_words, neut_words = {}, {}, {}
    nb_words = 0
    n_grams = 1
    min_len = -1

    def __init__(self, lang, min_len, n_grams, method="PRESENCE", verbose=False):
        self.lang = lang
        self.verbose = verbose
        self.method = method
        self.n_grams = n_grams
        self.min_len = min_len
        self.name += "-" + method + "_" + str(n_grams) + "G_min" + str(self.min_len)
        return

    def fit(self, x, y):
        if self.verbose:
            print("Fitting .....")
        self.x = x.copy()
        self.y = y.copy()
        self.scores = np.arange(len(x), dtype=float)
        if self.verbose:
            print("Fitting: construct words ...")
        self.neg_words, self.pos_words, self.neut_words = tweet_parser.construct_words(self.x, self.y, self.min_len, self.n_grams, self.verbose)
        self.nb_words = len(self.neg_words) + len(self.pos_words) + len(self.neut_words)

    def predict(self, tweets):
        res = np.arange(len(tweets)) * -1
        tmp_sets = [self.neg_words, None, self.neut_words, None, self.pos_words]
        for ti in range(len(tweets)):
            # Predict each class: neg, neut, pos
            tmp_scores = [-1, -1, -1, -1, -1]
            for i in range(0, 5, 2):
                if len(tmp_sets[i]) == 0:
                    if self.verbose:
                        print("not counting class: " + str(i))
                    continue

                try:
                    grams = tweet_parser.ngrams(tweets[i].strip(" ").split(" "), int(self.n_grams))
                    grams = [var for var in grams if var]  # remove ''
                except:
                    if self.verbose:
                        print("error split with: " + str(tweets[i]))
                    continue

                p = 1
                w_occ_tweet = 0
                for gram in grams:
                    # construct index: word1_word2_word3....
                    index = gram[0]
                    w_occ_tweet += tweets[ti].count(index)
                    for i_word in range(1, len(gram)):
                        index += "_" + gram[i_word]
                        w_occ_tweet += tweets[ti].count(gram[i_word])

                    nb_occ_w = 0
                    if index in tmp_sets[i]:
                        nb_occ_w = tmp_sets[i][index]

                    if self.method == "FREQUENCY":
                        p *= ((nb_occ_w + 1) / (len(tmp_sets[i]) + self.nb_words)) ** w_occ_tweet
                    else:
                        p *= (nb_occ_w + 1) / (len(tmp_sets[i]) + self.nb_words)

                    p *= len(np.where(self.y == i))
                tmp_scores[i] = p

            res[ti] = np.argmax(tmp_scores)
            # re balance
            if abs(tmp_scores[0] - tmp_scores[4]) < 0.1:
                res[ti] = 2
            if self.verbose:
                print("tweet: " + str(tweets[ti] + ", scores: 0=" + str(tmp_scores[0]) + ", scores: 2=" + str(
                    tmp_scores[2]) + ", scores: 4=" + str(tmp_scores[4])))
        return res


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("-t", "--tweet", type=str, help="tweet message", required=True)
    parser.add_argument("-m", "--method", type=str, help="freq or presence", required=True)
    parser.add_argument("-g", "--grams", type=str, help="tweet csv file to clean", required=True)
    parser.add_argument("-min", "--min", type=str, help="minim word length", required=True)
    args = parser.parse_args()

    bayes = BayesClassifier("ANG", args.min, args.grams, method=args.method)
    df = tweet_parser.get_stanford_train()
    bayes.fit(df.MSG, df.SCORE)

    args.tweet = tweet_parser.clean_tweet(args.tweet)
    score = bayes.predict([args.tweet])[0]

    print(json.dumps(str(score)))
    return 0


if __name__ == "__main__":
    main()
    exit(0)
