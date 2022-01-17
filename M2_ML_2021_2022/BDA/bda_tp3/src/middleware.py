import psycopg2
from psycopg2.extras import execute_values
from collections import namedtuple

Article = namedtuple("Article", ("article_id", "content", "published_date"))


class ArticleMiddleware:
    def __init__(self, ip):
        self.db = psycopg2.connect(host=ip, database="article", user="postgres")

    def get_article(self, a_id):
        with self.db:
            with self.db.cursor() as curs:
                curs.execute("SELECT * from articles WHERE article_id = %s", (a_id,))
                return list(map(lambda a: Article(*a), curs.fetchall()))

    def get_articles_dsc(self):
        with self.db:
            with self.db.cursor() as curs:
                curs.execute("SELECT * FROM get_all()")
                return list(map(lambda a: Article(*a), curs.fetchall()))

    def add_article(self, a_content):
        with self.db:
            with self.db.cursor() as curs:
                curs.execute("SELECT insert_article (%s)", (a_content,))
                return curs.fetchone()

    def add_articles(self, articles):
        with self.db:
            with self.db.cursor() as curs:
                execute_values(curs, "INSERT INTO articles (content) VALUES %s", (articles,))

    def update_article(self, a_id, a_content):
        with self.db:
            with self.db.cursor() as curs:
                curs.execute("SELECT * FROM update_article(%s,%s)", (a_id, a_content))
                return curs.fetchall()

    def remove_article(self, a_id):
        with self.db:
            with self.db.cursor() as curs:
                curs.execute("DELETE FROM articles WHERE article_id = %s", (a_id))

    def add_tag(self, a_id, tags):
        with self.db:
            with self.db.cursor() as curs:
                curs.execute("SELECT insert_tag(%s, %s)", (a_id, tags))
                return curs.fetchone()