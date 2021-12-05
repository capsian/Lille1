#!/usr/bin/python3

import re, string, os.path, argparse, sys
import pandas as pd

import spacy

import nltk
from nltk.stem.snowball import SnowballStemmer
from nltk.corpus import stopwords

# corpus
nlp = spacy.load("fr_core_news_lg")


def parse_args():
    parser = argparse.ArgumentParser(prog='Text Preprocessor', description='Lemmatize or Stemm dataset')
    parser.add_argument("-v", "--verbose", help="increase output verbosity", action="store_true")
    parser.add_argument("-in", "--input_file", help="input dataset", required=True)
    parser.add_argument("-op", "--operation", help="input model", choices=['l', 's'], required=True)
    _args = parser.parse_args()

    return _args


def reformat(msg):
    msg = msg.replace('\r', ' ')
    msg = msg.replace('\n', ' ')
    msg = msg.lower()
    # remove digits
    msg = re.sub(r'\d+', '', msg)
    # remove ponctuation
    msg = msg.translate(str.maketrans(' ', ' ', string.punctuation))
    #msg = re.sub(r'\.|\,|\n|\r|\_|\“|\"|\”|\?|\!|\:|\;|\(|\)|\[|\]', ' ', msg)
    # remove multiple space
    msg = re.sub(' +', ' ', msg)
    msg = msg.strip()
    return msg


def text_lemmatizer(df, verbose=False):
    # result
    result = []

    for i, (rc, rt) in enumerate(zip(df["review_content"], df["review_title"])):
        # concat title and review
        msg = str(rt) + " " + str(rc)

        # reformat
        msg = reformat(msg)

        # lemmatizer
        doc = nlp(msg)
        tokens = [token.lemma_ for token in doc if token.lemma_ not in stopwords.words('french')]

        # join: reformat sentence
        msg_clean = " ".join(tokens)

        result += [msg_clean]

        if verbose and i % 1000 == 0:
            print(i)

    # add review stars as dummy
    d_res = pd.get_dummies(df["review_stars"])
    d_res['msg'] = result

    return d_res


def text_stemmer(df, verbose=False):
    stemmer = SnowballStemmer(language='french')

    # result
    result = []

    for i, (rc, rt) in enumerate(zip(df["review_content"], df["review_title"])):
        # concat title and review
        msg = str(rt) + " " + str(rc)

        # reformat
        msg = reformat(msg)

        doc = nlp(msg)
        tokens = []
        for token in doc:
            t_stemm = stemmer.stem(str(token))
            if t_stemm not in stopwords.words('french'):
                tokens += [t_stemm]

        # join: reformat sentence
        result += [" ".join(tokens)]

        if verbose and i % 1000 == 0:
            print(i)

    # add review stars as dummy
    d_res = pd.get_dummies(df["review_stars"])
    d_res['msg'] = result

    return d_res


def main(_args):
    # read csv
    if _args.verbose:
        print("Loading dataset")
    df = pd.read_csv(_args.input_file).dropna()

    # process
    if _args.operation == 'l':
        output_name = os.path.splitext(os.path.basename(_args.input_file))[0] + "_lemmatized.csv"
        df_result = text_lemmatizer(df, verbose=_args.verbose)
    else:
        output_name = os.path.splitext(os.path.basename(_args.input_file))[0] + "_stemm.csv"
        df_result = text_stemmer(df, verbose=_args.verbose)

    # result
    df_result['target'] = df["Target"]

    # result file
    output_path = os.path.dirname(os.path.abspath(_args.input_file))
    if _args.verbose:
        print("output_name:", output_name)
        print("output_path:", output_path)

    df_result.to_csv(output_path + "/" + output_name, index=False)

    return 0


if __name__ == "__main__":
    # stop words
    nltk.download('stopwords')

    args = parse_args()
    sys.exit(main(args))
