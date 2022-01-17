import json

import pandas as pd
from flask import Flask, jsonify, request
from sklearn.feature_extraction.text import TfidfVectorizer
from text_preprocessor import text_lemmatizer, reformat
import spacy
from scipy import sparse
from nltk.corpus import stopwords
from sklearn.naive_bayes import MultinomialNB

app = Flask(__name__)

print("Load spacy")
nlp = spacy.load("fr_core_news_lg")

print("Read corpus")
corpus = pd.read_csv("./dataset/train_master_lemmatized.csv").dropna()
vectoriser = TfidfVectorizer(max_features=50000, ngram_range=(1, 3))
print("Fit")
tf_transformer = vectoriser.fit(corpus['msg'])
print("Fit_Transform")
vec = vectoriser.fit_transform(corpus['msg'])
# add review stars
vec = sparse.hstack((vec, sparse.csr_matrix(corpus.drop(['target', 'msg'], axis=1).values)))
# clf
print("clf fit")
clf = MultinomialNB().fit(vec, corpus['target'])


@app.route('/predict', methods=['POST'])
def predict():
    req = json.loads(request.data)
    print(req)

    # concat title and review
    msg = str(req['review_title']) + " " + str(req['review_content'])

    # reformat
    msg = reformat(msg)

    # lemmatizer
    doc = nlp(msg)
    tokens = [token.lemma_ for token in doc if token.lemma_ not in stopwords.words('french')]

    # join: reformat sentence
    msg_clean = " ".join(tokens)

    print(msg_clean)

    tf1_new = TfidfVectorizer(ngram_range=(1, 3), max_features=50000, vocabulary=tf_transformer.vocabulary_)
    X_tf1 = tf1_new.fit_transform([msg_clean])

    tmp_df = pd.DataFrame()
    for i in range(1, 6):
        tmp_df[str(i)] = [1 if req['review_stars'] == str(i) else 0]


    # add review stars
    X_tf1 = sparse.hstack((X_tf1, sparse.csr_matrix(tmp_df.values)))

    pred = clf.predict(X_tf1)
    score = clf.predict_proba(X_tf1)

    print(pred)
    return jsonify({'prediction': str(pred), 'score': str(score)})


# driver function
if __name__ == '__main__':
    app.run(debug=True)
