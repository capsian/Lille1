from tagger import *
from middleware import *
import time

word_freq = json.load(open('./data/lexique.json', "r"))
df_articles = get_articles_df('./data/paragraphes.json')
a_middleware = ArticleMiddleware(ip="172.28.101.85")

start = time.time()
for article in df_articles["article"]:
    _ = a_middleware.add_article(article)
end = time.time()

print("Time exec :", end-start)