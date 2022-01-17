#!/usr/local/bin/python

import pandas as pd

import cross_validation
import tweet_classifier_bayes
import tweet_classifier_keyword
import tweet_parser

print("Read ....")
df_train = pd.read_csv("data/training/training.1600000.processed.noemoticon.clean.csv")
df_test = pd.read_csv("data/test/testdata.manual.2009.06.14.clean.csv")

print("Cleaning ....")
df_train["MSG"] = df_train["MSG"].apply(tweet_parser.clean_tweet)
df_train.drop_duplicates(inplace=True, subset=['MSG'])
df_train.dropna(inplace=True)

df_test["MSG"] = df_test["MSG"].apply(tweet_parser.clean_tweet)
df_test.drop_duplicates(inplace=True, subset=['MSG'])
df_test.dropna(inplace=True)

for i in range(1, 5):
    for w in range(1, 4):
        bayes_pres = tweet_classifier_bayes.BayesClassifier("ANG", w, i, method="PRESENCE")
        bayes_freq = tweet_classifier_bayes.BayesClassifier("ANG", w, i, method="FREQUENCY")
        keyword = tweet_classifier_keyword.KeywordClassifier("ANG", i, w)
        bayes_pres.fit(df_train["MSG"].values, df_train["SCORE"].values)
        bayes_freq.fit(df_train["MSG"].values, df_train["SCORE"].values)
        keyword.fit(df_train["MSG"].values, df_train["SCORE"].values)
        pred_pres = bayes_pres.predict(df_test["MSG"].values)
        pred_freq = bayes_freq.predict(df_test["MSG"].values)
        pred_keyword = keyword.predict(df_test["MSG"].values)
        accuracy1, precision1, recall1, f1_score1 = cross_validation.scores(pred_pres, df_test["SCORE"].values)
        accuracy2, precision2, recall2, f1_score2 = cross_validation.scores(pred_freq, df_test["SCORE"].values)
        accuracy3, precision3, recall3, f1_score3 = cross_validation.scores(pred_keyword, df_test["SCORE"].values)
        print("bayes_pres: n_gram:%d, min_word:%d, accuracy:%s, precision:%s, recall:%s, f1_score:%s" % (i, w, accuracy1, precision1, recall1, f1_score1))
        print("pred_freq: n_gram:%d, min_word:%d, accuracy:%s, precision:%s, recall:%s, f1_score:%s" % (i, w, accuracy2, precision2, recall2, f1_score2))
        print("pred_keyword: n_gram:%d, min_word:%d, accuracy:%s, precision:%s, recall:%s, f1_score:%s" % (i, w, accuracy3, precision3, recall3, f1_score3))

