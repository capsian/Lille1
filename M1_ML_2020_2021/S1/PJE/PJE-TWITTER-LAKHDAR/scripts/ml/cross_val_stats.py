#!/usr/local/bin/python

import pandas as pd

import cross_validation
import tweet_classifier_bayes
import tweet_classifier_keyword
import tweet_classifier_knn
import tweet_parser

print("Read ....")
df_test = pd.read_csv("data/test/testdata.manual.2009.06.14.clean.csv")

print("Cleaning ....")
df_test["MSG"] = df_test["MSG"].apply(tweet_parser.clean_tweet)
df_test.drop_duplicates(inplace=True, subset=['MSG'])
df_test.dropna(inplace=True)

print("Keyword Classifier")

for i in range(1, 5):
    for m in range(1, 4):
        keyword = tweet_classifier_keyword.KeywordClassifier("ANG", i, m)
        cross_validation.cross_val(df_test["MSG"].values, df_test["SCORE"].values, 10, keyword, True)

for i in range(1, 5):
    for m in range(1, 4):
        bayes_pres = tweet_classifier_bayes.BayesClassifier("ANG", m, i, method="PRESENCE")
        cross_validation.cross_val(df_test["MSG"].values, df_test["SCORE"].values, 10, bayes_pres, True)

for i in range(1, 5):
    for m in range(1, 4):
        bayes_freq = tweet_classifier_bayes.BayesClassifier("ANG", m, i, method="FREQUENCY")
        cross_validation.cross_val(df_test["MSG"].values, df_test["SCORE"].values, 10, bayes_freq, True)

for i in range(0, 20, 5):
    if i == 0:
        i = 1
    knn = tweet_classifier_knn.KNNClassifier("ANG", i, tweet_classifier_knn.dist_simple)
    cross_validation.cross_val(df_test["MSG"].values, df_test["SCORE"].values, 10, knn, True)
