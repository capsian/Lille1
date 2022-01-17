CREATE OR REPLACE FUNCTION tag(_article TEXT)
  RETURNS TEXT[]
AS $$
    import string
    import re
    import pandas as pd
    import numpy as np
    import json

    _word_freq = json.load(open('./lexique.json', "r"))

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
$$ LANGUAGE plpythonu;

SELECT tag("Bonjour je suis à Poiter");