#!/usr/bin/python3

import redis
import os


def connection_redis(db_num):
    return redis.Redis(host="172.28.101.85", port=6379, password="password", db=db_num, decode_responses=True)


def exit_error(msg):
    print("Status:400")
    print("Content-type:text/html\r\n\r\n")
    print("<html>")
    print("<head>")
    print("<title>Error</title>")
    print("</head>")
    print("<body>")
    print("<h2>" + msg + "</h2>")
    print("</body>")
    print("</html>")
    exit(0)


def display_success(user="", user_uuid="", password="", cookie="", msg="", cookie_age=600):
    print("Status:200")
    if len(str(cookie)) > 0:
        print("Set-Cookie: sessionId=" + str(cookie) + "; Max-Age=" + str(cookie_age))
    print("Content-type:text/html\r\n\r\n")
    print("<html>")
    print("<head>")
    print("<title>Success</title>")
    print("</head>")
    print("<body>")
    print("<h2>")
    if len(str(user)) > 0:
        print("User: " + str(user))
    if len(str(user_uuid)) > 0:
        print("User_uuid: " + str(user_uuid))
    if len(str(password)) > 0:
        print("Password: " + str(password))
        print("Hashed Password: " + hashlib.sha1(str(password).encode('utf-8')).hexdigest())
    if len(str(cookie)) > 0:
        print("cookie: sessionId: " + str(cookie))
    print("</h2>")
    if len(str(msg)) > 0:
        print("<p>")
        print(str(msg))
        print("<p>")
    print("</body>")
    print("</html>")
    exit(0)


def display_json(user_info, cookie, cookie_age=600):
    print("Status:200")
    print("Set-Cookie: sessionId=" + str(cookie) + "; Max-Age=" + str(cookie_age))
    print("Content-type:application/json\r\n\r\n")
    print(user_info)
    exit(0)


def get_uuid_from_cookie(cookie):
    r5 = connection_redis(5)
    user_uuid = r5.get(cookie)
    r5.close()
    return user_uuid


def get_cookie(_match):
    # Returns the value from the matching cookie or '' if not defined.
    if 'HTTP_COOKIE' in os.environ:
        cookies = os.environ['HTTP_COOKIE']
        cookies = cookies.split('; ')

        for cookie in cookies:
            (_name, _value) = cookie.split('=')
            if _match.lower() == _name.lower():
                return _value
    return ''


def check_cookie():
    # get sessionId cookie (typo ?)
    session_cookie = get_cookie('sessionID')
    if len(session_cookie) == 0:
        exit_error('no session cookie !')

    # get user_uuid
    user_uuid = get_uuid_from_cookie(session_cookie)
    if user_uuid is None:
        exit_error("invalid session cookie")
    # print('user_uuid:', user_uuid)
    return user_uuid, session_cookie


def get_method():
    if "REQUEST_METHOD" in os.environ:
        return os.environ['REQUEST_METHOD']
    return ""
