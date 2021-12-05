#!/usr/bin/python3

import argparse, sys, re, string

import pandas as pd
import numpy as np
from sklearn.feature_extraction.text import TfidfVectorizer
from nltk.corpus import stopwords

from scipy import sparse

import spacy
from spacy.lang.fr.examples import sentences

from sklearn.linear_model import Ridge, SGDClassifier, LogisticRegression, Lasso
from sklearn.ensemble import RandomForestClassifier
from sklearn.naive_bayes import GaussianNB

from sklearn.model_selection import train_test_split
from sklearn.metrics import roc_auc_score

import pickle

random_state = 59

pd.set_option("display.max_columns", None)


def parse_args():
    available_models = ['sgd', 'rdg', 'lr', 'lasso', 'gnb', 'rf']
    parser = argparse.ArgumentParser(prog='models', description='Text classification score models')
    parser.add_argument("-v", "--verbose", help="increase output verbosity", action="store_true")
    parser.add_argument("-in", "--input_file", help="input dataset", required=True)
    parser.add_argument("-m", "--model", help="input model", choices=available_models)
    parser.add_argument("-lm", "--load_model", help="load model", required=False)
    parser.add_argument("-sm", "--save_model", help="save model", required=False)
    _args = parser.parse_args()

    if _args.model is None and _args.load_model is None:
        print("Input a model or a saved model !")
        exit(1)

    return _args


def vectorizer(df, ngram=(1, 3), max_features=50000):
    # vectoriser = TfidfVectorizer(max_features=max_features, ngram_range=ngram, min_df=0.01, max_df=0.95)
    vectoriser = TfidfVectorizer(max_features=max_features, ngram_range=ngram)

    vec = vectoriser.fit_transform(df['msg'])
    # add review stars
    vec = sparse.hstack((vec, sparse.csr_matrix(df.drop(['target', 'msg'], axis=1).values)))

    X_train, X_test, y_train, y_test = train_test_split(vec, df['target'], test_size=0.3, random_state=random_state)
    return X_train, X_test, y_train, y_test


def sgd_classifier(X_train, y_train, X_test, y_test):
    clf = SGDClassifier(random_state=random_state)
    pred = clf.fit(X_train, y_train).predict(X_test)
    return clf, roc_auc_score(y_test, pred)


def ridge_classifier(X_train, y_train, X_test, y_test):
    clf = Ridge(random_state=random_state)
    pred = clf.fit(X_train, y_train).predict(X_test)
    return clf, roc_auc_score(y_test, pred)


def logreg_classifier(X_train, y_train, X_test, y_test):
    clf = LogisticRegression(solver='lbfgs', max_iter=10000, penalty="l2", random_state=random_state)
    pred = clf.fit(X_train, y_train).predict(X_test)
    return clf, roc_auc_score(y_test, pred)


def lasso_classifier(X_train, y_train, X_test, y_test):
    clf = Lasso(alpha=0.1, random_state=random_state)
    pred = clf.fit(X_train, y_train).predict(X_test)
    return clf, roc_auc_score(y_test, pred)


def gaussianNB_classifier(X_train, y_train, X_test, y_test):
    clf = GaussianNB()
    pred = clf.fit(X_train, y_train).predict(X_test)
    return clf, roc_auc_score(y_test, pred)


def rndForest_classifier(X_train, y_train, X_test, y_test):
    clf = RandomForestClassifier(random_state=random_state)
    pred = clf.fit(X_train, y_train).predict(X_test)
    return clf, roc_auc_score(y_test, pred)


def save_model(clf, filename):
    pickle.dump(clf, open(filename, 'wb'))


def load_model(file_path):
    return pickle.load(open(file_path, 'rb'))


def main(_args):
    # read csv
    if _args.verbose:
        print("Loading dataset")
    df = pd.read_csv(_args.input_file).dropna()

    # vectorize and split
    if _args.verbose:
        print("Vectorize and split")
    X_train, X_test, y_train, y_test = vectorizer(df)

    # compute from saved model
    if _args.load_model is not None:
        if _args.verbose:
            print("Loading model", _args.load_model)
        clf = load_model(_args.load_model)
        pred = clf.fit(X_train, y_train).predict(X_test)
        print('roc_auc_score:', roc_auc_score(y_test, pred))
        return 0

    if _args.verbose:
        print("Evaluating with model", _args.model)
    # switch
    model_switch = {
        'sgd': sgd_classifier,
        'rdg': ridge_classifier,
        'lr': logreg_classifier,
        'lasso': lasso_classifier,
        'gnb': gaussianNB_classifier,
        'rf': rndForest_classifier,
    }
    clf, score = model_switch[_args.model](X_train, y_train, X_test, y_test)

    print(_args.model, "roc_auc_score:", score)

    if _args.save_model is not None:
        save_model(clf, _args.save_model)

    return 0


if __name__ == "__main__":
    args = parse_args()
    sys.exit(main(args))
