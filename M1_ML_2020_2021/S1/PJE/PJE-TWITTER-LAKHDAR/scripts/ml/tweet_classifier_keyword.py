#!/usr/local/bin/python3

import argparse
import json

import numpy as np

import tweet_parser


class KeywordClassifier:
    name = "KeywordClassifier"
    lang, verbose = None, False
    pos_words, neg_words, neut_words = {}, {}, {}
    x, y = {}, {}
    n_grams = 1
    min_len = -1

    def __init__(self, lang, n_grams, min_len, verbose=False):
        self.lang = lang
        self.n_grams = n_grams
        self.verbose = verbose
        self.min_len = min_len
        self.name += "_" + str(n_grams) + "G_min" + str(self.min_len)

        # if lang == "FR":
        #    tmp_pos = pd.read_csv(
        #        '/home/alpha/go/src/gitlab-etu.fil.univ-lille1.fr/lakhdar/PJE-TWITTER-LAKHDAR/data/training/positive_words_fr.csv')
        #    tmp_neg = pd.read_csv(
        #        '/home/alpha/go/src/gitlab-etu.fil.univ-lille1.fr/lakhdar/PJE-TWITTER-LAKHDAR/data/training/negative_words_fr.csv')
        # elif lang == "ANG":
        #    tmp_pos = pd.read_csv(
        #        '/home/alpha/go/src/gitlab-etu.fil.univ-lille1.fr/lakhdar/PJE-TWITTER-LAKHDAR/data/training/positive_words_ang.csv')
        #    tmp_neg = pd.read_csv(
        #        '/home/alpha/go/src/gitlab-etu.fil.univ-lille1.fr/lakhdar/PJE-TWITTER-LAKHDAR/data/training/negative_words_ang.csv')
        # else:
        #    raise Exception("invalid lang: " + str(lang))

        # for elem in tmp_pos.values:
        #    if elem[0] not in self.pos_words:
        #        self.pos_words[elem[0]] = 1
        #    else:
        #        self.pos_words[elem[0]] += 1
        #
        # for elem in tmp_neg.values:
        #    if elem[0] not in self.neg_words:
        #        self.neg_words[elem[0]] = 1
        #    else:
        #        self.neg_words[elem[0]] += 1
        return

    def fit(self, x, y):
        self.x = x.copy()
        self.y = y.copy()
        tmp_neg, tmp_pos, tmp_neut = tweet_parser.construct_words(x, y, self.min_len, self.n_grams, self.verbose)
        self.pos_words.update(tmp_pos)
        self.neg_words.update(tmp_neg)
        self.neut_words.update(tmp_neut)

    def predict(self, tweets):
        res = np.arange(len(tweets)) * -1
        for i in range(len(tweets)):
            try:
                grams = tweet_parser.ngrams(tweets[i].strip(" ").split(" "), int(self.n_grams))
                grams = [var for var in grams if var]  # remove ''
            except:
                if self.verbose:
                    print("error split with: " + str(tweets[i]))
                continue

            nb_neut, nb_pos, nb_neg = 0, 0, 0
            for gram in grams:
                # construct index: word1_word2_word3....
                index = gram[0]
                for i_word in range(1, len(gram)):
                    index += "_" + gram[i_word]

                if index in self.pos_words:
                    nb_pos += self.pos_words[index]
                if index in self.neg_words:
                    nb_neg += self.neg_words[index]
                if index in self.neut_words:
                    nb_neut += self.neut_words[index]

            if nb_pos == nb_neg:
                res[i] = 2
            else:
                res[i] = np.argmax([nb_neg, -1, nb_neut, -1, nb_pos])

            if self.verbose:
                print(
                    str(res[i]) + ": " + tweets[i] + " || nb_neg: " + str(nb_neg) + ", nb_neut: " + str(nb_neut) + ", nb_pos: " + str(nb_pos))
        return res


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("-t", "--tweet", type=str, help="tweet message", required=True)
    parser.add_argument("-g", "--grams", type=str, help="tweet csv file to clean", required=True)
    parser.add_argument("-v", "--verbose", help="tweet csv file to clean", action="store_true")
    parser.add_argument("-min", "--min", type=str, help="minim word length", required=True)
    args = parser.parse_args()

    keyword_clf = KeywordClassifier("ANG", args.grams, args.min, args.verbose)
    df = tweet_parser.get_stanford_train()
    keyword_clf.fit(df.MSG, df.SCORE)

    args.tweet = tweet_parser.clean_tweet(args.tweet)
    score = keyword_clf.predict([args.tweet])[0]

    print(json.dumps(str(score)))
    return 0


if __name__ == "__main__":
    main()
    exit(0)
