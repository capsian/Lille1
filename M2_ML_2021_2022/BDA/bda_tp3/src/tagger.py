import string
import re
import pandas as pd
import numpy as np
import json


def get_word_freq_df(filepath):
    word_freq = json.load(open(filepath, "r"))
    ws, fs = [], []
    for w in word_freq:
        ws += [w]
        fs += [word_freq[w]]

    df = pd.DataFrame(columns=["word", "frequency"])
    df['word'] = ws
    df['frequency'] = fs
    return df


def get_articles_df(filepath):
    articles = json.load(open(filepath, "r"))
    la = []
    for a in articles:
        la += [str(a)]

    df = pd.DataFrame(columns=["article"])
    df['article'] = la
    return df


def tag_article1(_article, _word_freq):
    translation_table = str.maketrans('', '', string.digits + string.punctuation)

    _article = _article.lower()
    _article = re.sub(r"\W+", " ", _article)

    words = []
    words_prob = []
    for word in _article.split(" "):
        word = word.translate(translation_table)
        # take word with specific len
        if 5 <= len(word) <= 15:
            if word not in words:
                if word in _word_freq:
                    words += [word]
                    words_prob += [_word_freq[word]]

    # if no selected words: take the 5 first ones
    if len(words) == 0:
        for i in range(5):
            words += [_article.split(" ")[i].translate(translation_table)]
            words_prob += [i+1]

    tags = []
    for _ in range(5):
        pos = np.argmax(words_prob)
        tags += [words[pos]]
        words_prob[pos] = 0

    return tags
