#!/usr/bin/python3

import cgi
import cgitb
import hashlib
import uuid
import datetime
from utils import connection_redis

# Create instance of FieldStorage
form = cgi.FieldStorage()

# Get data from fields
user = form.getvalue('user')
password = form.getvalue('password')

# connect to db 1
r1 = connection_redis(1)

# User already present
if r1.get(user) is not None:
    print("Status:400")
    print("Content-type:text/html\r\n\r\n")
    print("<html>")
    print("<head>")
    print("<title>Create error</title>")
    print("</head>")
    print("<body>")
    print("<h2>User", user, "already present !</h2>")
    print("</body>")
    print("</html>")
else:
    h_password = hashlib.sha1(str(password).encode('utf-8')).hexdigest()
    u_uuid = uuid.uuid4()
    # add { user = uuid } to db 1
    r1.set(user, str(u_uuid))
    # set hashmap user_info to db 2
    r2 = connection_redis(2)
    d = str(datetime.datetime.now())
    r2.hset(str(u_uuid), "user", user)
    r2.hset(str(u_uuid), "password", h_password)
    r2.hset(str(u_uuid), "last_connection", d)
    r2.hset(str(u_uuid), "creation_date", d)
    print("Status:200")
    print("Content-type:text/html\r\n\r\n")
    print("<html>")
    print("<head>")
    print("<title>Create success</title>")
    print("</head>")
    print("<body>")
    print("<h2>" + str(d) + " - User", user, "with password", password, ":", h_password, "and uuid", str(u_uuid),
          "created !</h2>")
    print("</body>")
    print("</html>")
