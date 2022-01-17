#!/usr/bin/python3

import cgi
import cgitb
import hashlib
import uuid
import datetime
import os
from utils import *

user_cookie = get_cookie('sessionID')
if len(user_cookie) == 0:
    exit_error('no session cookie !')

# get user_uuid from user_cookie
r5 = connection_redis(5)
user_uuid = r5.get(str(user_cookie))
if user_uuid is None:
    exit_error("cookie not set server side ! user_cookie:" + str(user_cookie))

# get user info from user_uuid
r2 = connection_redis(2)
user_info = r2.hgetall(str(user_uuid))
if user_info is None:
    exit_error("couldn't retrieve user info from user_uuid:" + str(user_uuid))

# update cookie expiration
r5.expire(str(user_cookie), 600)

# display user_info as json
user_info['user_uuid'] = user_uuid
display_json(user_info, user_cookie)

# close
r2.close()
r5.close()
