#!/usr/bin/python3

import cgi
import cgitb
import hashlib
import uuid
import datetime
from utils import *

# Create instance of FieldStorage
form = cgi.FieldStorage()

# Get data from fields
user = form.getvalue('user')
password = form.getvalue('password')

# check if exists in db 1
r1 = connection_redis(1)
user_uuid = r1.get(user)
if user_uuid is None:
    exit_error("User unknown")

# get user info
r2 = connection_redis(2)
user_info = r2.hgetall(str(user_uuid))
# check password
if user_info['password'] != hashlib.sha1(str(password).encode('utf-8')).hexdigest():
    exit_error("Wrong password")

# set cookie user_cookie = user_uuid in db5 with 10min expiration
user_cookie = uuid.uuid4()
r5 = connection_redis(5)
r5.set(str(user_cookie), str(user_uuid))
r5.expire(str(user_cookie), 600)

# update connection_timestamp
r2.hset(str(user_uuid), "last_connection", str(datetime.datetime.now()))

# display
msg = "Connection succeed !"
display_success(msg=msg, user=user, user_uuid=user_uuid, password=user_info['password'], cookie=user_cookie)

# close
r1.close()
r2.close()
r5.close()
