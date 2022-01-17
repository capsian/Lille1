import psycopg2
from collections import namedtuple
from time import time

Message = namedtuple("Message", ("message_id", "content", "date", "replies_to", "user_name", "user_id"))


def logged(f):
    def nf(self, *args, **kwargs):
        t0 = time()
        r = f(self, *args, **kwargs)
        self.acc_time += time() - t0
        self.nb_query += 1
        return r

    return nf


class microblog:
    def __init__(self, ip):
        self.db = psycopg2.connect(host=ip, database="microblog", user="common_user")
        self.acc_time = 0
        self.nb_query = 0

    @logged
    def publish_post(self, user, password, content, mid=None):
        """"
            publish a post for user "user". If mid is set to some message id, will act as a reply to.
        """
        with self.db:
            with self.db.cursor() as curs:
                curs.execute("SELECT insert_message(%s, %s, %s, %s)", (user, password, content, mid))
                return curs.fetchone()[0]

    @logged
    def follow(self, user_id, password, other_id):
        """
            Make user_id follow a other_id
        """
        with self.db:
            with self.db.cursor() as curs:
                curs.execute("SELECT follow(%s, %s, %s)", (user_id, password, other_id))

    @logged
    def get_feed(self, user, password, limit=50):
        """
            Get the 50 fist message of the feed of user
        """
        with self.db:
            with self.db.cursor() as curs:
                curs.execute("SELECT * FROM feed(%s,%s) LIMIT %s", (user, password, limit))
                return list(map(lambda e: Message(*e), curs.fetchall()))

    @logged
    def get_messages(self):
        """
            Get last posted message
        """
        with self.db:
            with self.db.cursor() as curs:
                curs.execute("SELECT * FROM messages")
                return list(map(lambda e: Message(*e), curs.fetchall()))
