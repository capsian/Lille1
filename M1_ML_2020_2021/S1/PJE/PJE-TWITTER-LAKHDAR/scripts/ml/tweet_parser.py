#!/usr/local/bin/python
import argparse
import json
import os
import re

import numpy as np
import pandas as pd

f1 = "data/old/negative.txt"
f2 = "data/old/positive.txt"

stanford_train_csv = "data/old/training.1600000.processed.noemoticon.csv"
stanford_test_csv = "data/old/testdata.manual.2009.06.14.csv"


def get_positives_fr():
    f = open(f2, "r", encoding='iso-8859-1')
    _ = f.readline()
    l = f.readline().split(",")
    for i in range(len(l)):
        l[i] = l[i].strip(" ").strip("\n")
    return l


def get_positives_ang():
    f = open(f2, "r", encoding='iso-8859-1')
    l = f.readline().split(",")
    for i in range(len(l)):
        l[i] = l[i].strip(" ").strip("\n")
    return l


def get_negatives_fr():
    f = open(f1, "r", encoding='iso-8859-1')
    _ = f.readline()
    l = f.readline().split(",")
    for i in range(len(l)):
        l[i] = l[i].strip(" ").strip("\n")
    return l


def get_negatives_ang():
    f = open(f1, "r", encoding='iso-8859-1')
    l = f.readline().split(",")
    for i in range(len(l)):
        l[i] = l[i].strip(" ").strip("\n")
    return l


def construct_neg_pos():
    pos_fr = np.array(get_positives_fr())
    neg_fr = np.array(get_negatives_fr())
    pos_ang = np.array(get_positives_ang())
    neg_ang = np.array(get_negatives_ang())

    pd.DataFrame(pos_fr).to_csv("data/training/positive_words_fr.csv", index=None, header=["WORDS"], quotechar='"', quoting=1)
    pd.DataFrame(neg_fr).to_csv("data/training/negative_words_fr.csv", index=None, header=["WORDS"], quotechar='"', quoting=1)
    pd.DataFrame(pos_ang).to_csv("data/training/positive_words_ang.csv", index=None, header=["WORDS"], quotechar='"', quoting=1)
    pd.DataFrame(neg_ang).to_csv("data/training/negative_words_ang.csv", index=None, header=["WORDS"], quotechar='"', quoting=1)

    return


def format_stanford():
    columns = ["SCORE", "MSG"]

    df1 = pd.read_csv(stanford_train_csv, usecols=[0, 5], engine="python", names=columns)
    df1 = df1.reindex(columns=[columns[1], columns[0]])
    df1.to_csv("data/training.1600000.processed.noemoticon.clean.csv", index=False, header=True)

    # df2 = pd.read_csv(stanford_test_csv, usecols=[0, 5], engine="python", names=columns)
    # df2 = df2.reindex(columns=[columns[1], columns[0]])
    # df2.to_csv(
    #    "/home/alpha/go/src/gitlab-etu.fil.univ-lille1.fr/lakhdar/PJE-TWITTER-LAKHDAR/data/testdata.manual.2009.06.14.clean.csv",
    #    index=False)


def get_stanford_train():
    return pd.read_csv("data/training/training.1600000.processed.noemoticon.clean.csv")


def get_stanford_test():
    return pd.read_csv("data/training/testdata.manual.2009.06.14.clean.csv")


# https://github.com/s/preprocessor/blob/master/preprocessor/defines.py
def clean_tweet(tweet):
    try:
        regex_url = re.compile(r'http[s]?://(?:[a-zA-Z]|[0-9]|[$-_@.&+]|[!*\(\),]|(?:%[0-9a-fA-F][0-9a-fA-F]))+', re.IGNORECASE)
        regex_mention = re.compile(r'@\w*')
        regex_hashtag = re.compile(r'#\w*')
        regex_rt = re.compile(r'^(RT|FAV)')
        regex_emoji = re.compile(u'([\U00002600-\U000027BF])|([\U0001f300-\U0001f64F])|([\U0001f680-\U0001f6FF])')
        regex_smileys = re.compile(r"(\s?:X|:|;|=)(?:-)?(?:\)+|\(|O|D|P|S|\\|\/\s){1,}", re.IGNORECASE)
        regex_numbers = re.compile(r"(^|\s)(-?\d+([.,]?\d+)*)")
        regex_punctuation = re.compile(r'[^\w\s]')
        regex_spaces = re.compile(r' +')

        tweet = regex_spaces.sub(" ", tweet)
        tweet = regex_url.sub("", tweet)
        tweet = regex_mention.sub("", tweet)
        tweet = regex_hashtag.sub("", tweet)
        tweet = regex_rt.sub("", tweet)
        tweet = regex_emoji.sub("", tweet)
        tweet = regex_smileys.sub("", tweet)
        tweet = regex_numbers.sub("", tweet)
        tweet = regex_punctuation.sub("", tweet)
        tweet = " ".join(tweet.split())
    except:
        print("error clean with : " + str(tweet))

    return tweet


def clean_tweets(csv_path):
    df = pd.read_csv(csv_path, engine="python")
    # df.drop_duplicates(inplace=True, subset=['ID'])
    df["MSG"] = df["MSG"].apply(clean_tweet)
    df.drop_duplicates(inplace=True, subset=['MSG'])
    df.dropna(inplace=True)
    df.to_csv(csv_path, index=False, quotechar='"', quoting=1)
    return True


def get_all_csv_info():
    out = {}
    for f in os.listdir("data"):
        if f.endswith(".csv"):
            df = pd.read_csv("data/" + f, engine="python")
            out[f] = {
                "nb_tweets": len(df),
                "nb_tweets_pos": len(df[df["SCORE"] == 4]),
                "nb_tweets_neg": len(df[df["SCORE"] == 0]),
                "nb_tweets_neut": len(df[df["SCORE"] == 2]),
                "nb_tweets_todo": len(df[df["SCORE"] == -1])
            }

    print(json.dumps(out))
    return


# https://stackoverflow.com/questions/32441605/generating-ngrams-unigrams-bigrams-etc-from-a-large-corpus-of-txt-files-and-t
def ngrams(s, n=2, i=0):
    while len(s[i:i + n]) == n:
        yield s[i:i + n]
        i += 1


def construct_words(X, y, min_len, n_grams, debug=False):
    neg_words, pos_words, neut_words = {}, {}, {}
    neg_indices = np.array(np.where(y == 0)).ravel()
    pos_indices = np.array(np.where(y == 4)).ravel()
    neut_indices = np.array(np.where(y == 2)).ravel()

    tmp_indices = [neg_indices, pos_indices, neut_indices]
    tmp_words = [neg_words, pos_words, neut_words]

    for c in range(len(tmp_indices)):
        for c_tweet in X[tmp_indices[c]]:
            try:
                grams = ngrams(c_tweet.strip(" ").split(" "), int(n_grams))
                grams = [var for var in grams if var]  # remove ''
            except:
                if debug:
                    print("error split with: " + str(c_tweet))
                continue

            for gram in grams:
                index = ""
                if int(min_len) != -1 and len(gram[0]) > int(min_len):
                    index = gram[0]
                for i_word in range(1, len(gram)):
                    if int(min_len) != -1 and len(gram[i_word]) > int(min_len):
                        index += "_" + gram[i_word]
                if index not in tmp_words[c]:
                    tmp_words[c][index] = 1
                else:
                    tmp_words[c][index] += 1

    return neg_words, pos_words, neut_words


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("-c", "--clean", type=str, help="tweet csv file to clean")
    args = parser.parse_args()

    if len(args.clean) > 0:
        clean_tweets(args.clean)

    print(json.dumps(1))
    return 0


if __name__ == "__main__":
    main()
    exit(0)
