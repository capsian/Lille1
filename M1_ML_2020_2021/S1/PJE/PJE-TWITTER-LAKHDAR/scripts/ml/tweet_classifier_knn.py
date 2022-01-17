#!/usr/local/bin/python3

import argparse
import json
from collections import Counter

import numpy as np
from tqdm import tqdm

import tweet_parser


def dist_simple(msg1, msg2, verbose=False):
    msg1_words = msg1.strip(" ").split(" ")
    msg2_words = msg2.strip(" ").split(" ")

    len_msg1 = 0
    for e in msg1_words:
        len_msg1 += len(e)

    len_msg2 = 0
    for e in msg2_words:
        len_msg2 += len(e)

    nb_same = 0
    for e in msg1_words:
        if e in msg2_words:
            nb_same += 1

    if verbose:
        print("msg1: %s, msg2:%s" % (msg1, msg2))
        print("len_msg1: %d, len_msg2: %d, nb_same: %d | score: %d" % (
            len_msg1, len_msg2, nb_same, ((len_msg1 + len_msg2) - nb_same) / (len_msg1 + len_msg2)))

    return ((len_msg1 + len_msg2) - nb_same) / (len_msg1 + len_msg2)


def levenshtein(s1, s2):
    if len(s1) < len(s2):
        return levenshtein(s2, s1)

    # len(s1) >= len(s2)
    if len(s2) == 0:
        return len(s1)

    previous_row = range(len(s2) + 1)
    for i, c1 in enumerate(s1):
        current_row = [i + 1]
        for j, c2 in enumerate(s2):
            insertions = previous_row[
                             j + 1] + 1  # j+1 instead of j since previous_row and current_row are one character longer
            deletions = current_row[j] + 1  # than s2
            substitutions = previous_row[j] + (c1 != c2)
            current_row.append(min(insertions, deletions, substitutions))
        previous_row = current_row

    return previous_row[-1]


class KNNClassifier:
    name = "KNNClassifier"
    lang, scores = None, None
    verbose = False
    x, y = {}, {}

    def __init__(self, lang, k, dist_func, verbose=False):
        self.lang = lang
        self.verbose = verbose
        self.k = k
        self.dist_func = dist_func
        self.name += "-" + str(k)
        return

    def fit(self, x, y):
        if self.verbose:
            print("Fitting .....")
        self.x = x.copy()
        self.y = y.copy()
        self.scores = np.arange(len(x), dtype=float)

    def predict(self, tweets):
        res = np.arange(len(tweets)) * -1
        for it in range(len(tweets)):
            if self.verbose:
                print("Scoring .....")
                for i in tqdm(range(len(self.scores))):
                    try:
                        self.scores[i] = self.dist_func(tweets[it], self.x[i])
                    except:
                        print("score error with: " + str(tweets[it]) + ", with, " + str(self.x[i]))
                        self.scores[i] = -1
                        continue
            else:
                for i in range(len(self.scores)):
                    try:
                        self.scores[i] = self.dist_func(tweets[it], self.x[i])
                    except:
                        self.scores[i] = -1
                        continue

            # nearest k neighbours
            neighbors_indices = []
            for i in range(self.k):
                pos = np.argmin(self.scores)
                neighbors_indices += [pos]
                self.scores[pos] = np.Inf

            res[it] = Counter(self.y[neighbors_indices]).most_common(1)[0][0]

            if self.verbose:
                print(str(res[it]) + " : " + tweets[it])
                for n in neighbors_indices:
                    print(" neighbor " + str(n) + " msg: " + str(self.x[n]) + " - " + str(self.y[n]))

        return res


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("-t", "--tweet", type=str, help="tweet message", required=True)
    parser.add_argument("-k", "--k", type=int, help="neighbors", required=True)
    parser.add_argument("-d", "--dist_func", type=str, help="dist func", required=True)
    args = parser.parse_args()

    if args.dist_func == "dist_simple":
        knn = KNNClassifier("ANG", args.k, dist_simple)
    else:
        knn = KNNClassifier("ANG", args.k, levenshtein)

    df = tweet_parser.get_stanford_train()
    knn.fit(df.MSG, df.SCORE)

    args.tweet = tweet_parser.clean_tweet(args.tweet)
    score = knn.predict([args.tweet])[0]

    print(json.dumps(str(score)))
    return 0


if __name__ == "__main__":
    main()
    exit(0)
