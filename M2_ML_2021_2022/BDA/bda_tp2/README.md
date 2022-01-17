# BDA TP 2

## https://www.paperman.name/page/enseignement/2021/nosql/TD2.html

# Author

- Selim Lakhdar
    - selim.lakhdar.etu@univ-lille.fr
    - selim.lakhdar@gmail.com

# VM

- redis-1: 172.28.101.85
- redis-2: 172.28.100.172

# Setup

### redis.conf

```
bind 0.0.0.0
requirepass password
```

```
sudo ufw allow 6379
sudo ufw allow 6379/tcp
```

```
ubuntu@redis-1:~$ redis-cli 
127.0.0.1:6379> AUTH password
OK
```

### Walk-through

```
127.0.0.1:6379> AUTH password
OK
127.0.0.1:6379> SET big_answer "42"
OK
127.0.0.1:6379> GET big_answer
"42"
127.0.0.1:6379> SELECT 1
OK
127.0.0.1:6379[1]> GET big_answer
(nil)
```

- SELECT: Select the Redis logical database having the specified zero-based numeric index. New connections always use
  the database 0.
    - https://redis.io/commands/select

```
172.28.101.85:6379> AUTH password
OK
172.28.101.85:6379> select 1*
(error) ERR invalid DB index
172.28.101.85:6379> get test_python
(nil)
172.28.101.85:6379> select 1
OK
172.28.101.85:6379[1]> get test_python
"42"
```

```
curl 172.28.100.172/env.cgi
SERVER_NAME=172.28.100.172
SCRIPT_NAME=/env.cgi
REDIRECT_STATUS=200
GATEWAY_INTERFACE=CGI/1.1
SERVER_SOFTWARE=lighttpd/1.4.55
DOCUMENT_ROOT=/var/www/html
PWD=/var/www/html
REQUEST_URI=/env.cgi
REQUEST_SCHEME=http
QUERY_STRING=
HTTP_ACCEPT=*/*
REMOTE_PORT=47292
HTTP_HOST=172.28.100.172
SERVER_ADDR=172.28.100.172
HTTP_USER_AGENT=curl/7.68.0
SHLVL=1
CONTENT_LENGTH=0
SERVER_PROTOCOL=HTTP/1.1
SERVER_PORT=80
SCRIPT_FILENAME=/var/www/html/env.cgi
REMOTE_ADDR=172.28.101.85
REQUEST_METHOD=GET
_=/usr/bin/printenv
```

```
ubuntu@redis-1:~$ curl --data "Holla Mundo!" 172.28.100.172/env.cgi?halloWelt
SERVER_NAME=172.28.100.172
SCRIPT_NAME=/env.cgi
REDIRECT_STATUS=200
GATEWAY_INTERFACE=CGI/1.1
SERVER_SOFTWARE=lighttpd/1.4.55
DOCUMENT_ROOT=/var/www/html
PWD=/var/www/html
HTTP_CONTENT_LENGTH=12
REQUEST_URI=/env.cgi?halloWelt
REQUEST_SCHEME=http
QUERY_STRING=halloWelt
HTTP_ACCEPT=*/*
REMOTE_PORT=47294
HTTP_HOST=172.28.100.172
SERVER_ADDR=172.28.100.172
HTTP_USER_AGENT=curl/7.68.0
SHLVL=1
CONTENT_LENGTH=12
SERVER_PROTOCOL=HTTP/1.1
SERVER_PORT=80
SCRIPT_FILENAME=/var/www/html/env.cgi
REMOTE_ADDR=172.28.101.85
CONTENT_TYPE=application/x-www-form-urlencoded
REQUEST_METHOD=POST
_=/usr/bin/printenv
Holla Mundo!
```

# CGI avec Python

```
ubuntu@redis-1:~$ curl  172.28.100.172/env
CONTENT_LENGTH:0
QUERY_STRING:
REQUEST_URI:/env
REDIRECT_URI:/env.py
REDIRECT_STATUS:200
SCRIPT_NAME:/env.py
SCRIPT_FILENAME:/var/www/html/env.py
DOCUMENT_ROOT:/var/www/html
REQUEST_METHOD:GET
SERVER_PROTOCOL:HTTP/1.1
SERVER_SOFTWARE:lighttpd/1.4.55
GATEWAY_INTERFACE:CGI/1.1
REQUEST_SCHEME:http
SERVER_PORT:80
SERVER_ADDR:172.28.100.172
SERVER_NAME:172.28.100.172
REMOTE_ADDR:172.28.101.85
REMOTE_PORT:47310
HTTP_HOST:172.28.100.172
HTTP_USER_AGENT:curl/7.68.0
HTTP_ACCEPT:*/*
LC_CTYPE:C.UTF-8
```

# Redis Databases

- DB1
```json
  user_name: uuid_user
```

- DB2
```json
  "uuid_user": {
    "user": user,
    "password": h_password,
    "last_connection": timestamp,
    "creation_date": timestamp
  }
```

- DB3
```json
  "uuid_file": [V1, V2, V3, ....]
```

- DB4
```json
  "uuid_user": {
    uuid_file1: file1,
    uuid_file2: file2,
    uuid_file3: file3,
    .......
  }
```

- DB5
```json
  "uuid_token": uuid_user
```


# REST API for /files endpoint
## PUT
  - input sanity check
  - check if file is already present (with the name)
  - gen file_uuid
  - insert file (and file info) in db3 and db4
## GET
  - check if user have files
  - return user files list (with nb version)
## DELETE
  - input sanity check
  - check if the file is already present
  - delete it from db3 and db4
## PATCH
  - input sanity check
  - check if the file is already present
  - add new version to db3

# POC / Test

```shell
cd scripts && ./poc
==========================
Connect: to middleware
==========================

<html>
<head>
<title>Success</title>
</head>
<body>
<h2>
User: selim
User_uuid: b7c6e25f-7f92-4229-8827-03ec336fb6a9
Password: 4ea0e69a17994cc86b92a9971224f1ec18de5ea0

==========================
Info with token
==========================

{'user': 'selim', 'password': '4ea0e69a17994cc86b92a9971224f1ec18de5ea0', 'last_connection': '2021-10-29 17:23:50.982695', 'creation_date': '2021-10-09 20:23:26.414749', 'user_uuid': 'b7c6e25f-7f92-4229-8827-03ec336fb6a9'}

==========================
Upload file logo.png
==========================

<html>
<head>
<title>Success</title>
</head>
<body>
<h2>
User_uuid: b7c6e25f-7f92-4229-8827-03ec336fb6a9
cookie: sessionId: 0891ea43-2dbf-4ec3-bffd-830374a4ce40
</h2>
<p>
File logo.png with uuid2f6b3d3b-7fbe-4fbd-ab25-b5c23bf651bc uploaded !
<p>
</body>
</html>

==========================
Can't Upload same file (with same name)
==========================

<html>
<head>
<title>Error</title>
</head>
<body>
<h2>file already present !</h2>
</body>
</html>

==========================
Patch file logo.png (logo_2.png)
==========================

<html>
<head>
<title>Success</title>
</head>
<body>
<h2>
User_uuid: b7c6e25f-7f92-4229-8827-03ec336fb6a9
cookie: sessionId: 0891ea43-2dbf-4ec3-bffd-830374a4ce40
</h2>
<p>
Patch success ! nb_version:2
<p>
</body>
</html>

==========================
Get files
==========================

<html>
<head>
<title>Success</title>
</head>
<body>
<h2>
User_uuid: b7c6e25f-7f92-4229-8827-03ec336fb6a9
cookie: sessionId: 0891ea43-2dbf-4ec3-bffd-830374a4ce40
</h2>
<p>
User files: 
 - 2f6b3d3b-7fbe-4fbd-ab25-b5c23bf651bc : logo.png, nb_version: 2

<p>
</body>
</html>

==========================
Del non existent file
==========================

<html>
<head>
<title>Error</title>
</head>
<body>
<h2>File notpresent.png not present !</h2>
</body>
</html>

==========================
Del file
==========================

<html>
<head>
<title>Success</title>
</head>
<body>
<h2>
User_uuid: b7c6e25f-7f92-4229-8827-03ec336fb6a9
cookie: sessionId: 0891ea43-2dbf-4ec3-bffd-830374a4ce40
</h2>
<p>
Delete success !
<p>
</body>
</html>

==========================
Get files
==========================

<html>
<head>
<title>Error</title>
</head>
<body>
<h2>No files for this user !</h2>
</body>
</html>
```

