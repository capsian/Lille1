import time

from tagger import *
from middleware import *

a_middleware = ArticleMiddleware(ip="172.28.101.85")
word_freq = json.load(open('./data/lexique.json', "r"))

# load once
articles = a_middleware.get_articles_dsc()

# insert multiple
start = time.time()
for a in articles:
    tags = tag_article1(a[1], word_freq)
    a_middleware.add_tag(a[0], tags)
end = time.time()

print("Exec time:", end - start)
