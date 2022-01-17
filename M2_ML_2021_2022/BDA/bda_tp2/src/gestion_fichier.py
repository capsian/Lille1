#!/usr/bin/python3

import cgi
import cgitb
import hashlib
import uuid
import datetime
import os
from utils import *


def process_get(u_uuid, cookie):
    print("process_get: u_uuid", str(u_uuid))
    r4 = connection_redis(4)
    user_files = r4.hgetall(str(u_uuid))
    print("user_files:", user_files)
    r4.close()

    if user_files is None:
        exit_error("No files for this user !")
    if len(user_files.keys()) == 0:
        exit_error("No files for this user !")

    r3 = connection_redis(3)
    nb_versions = []
    for k in user_files:
        nb_versions += [r3.llen(k)]
    r3.close()

    n = 0
    msg = "User files: \n"
    for k in user_files:
        msg += " - " + str(k) + " : " + user_files[k] + ", nb_version: " + str(nb_versions[n]) + "\n"
        n += 1

    display_success(user_uuid=u_uuid, msg=msg, cookie=cookie)


def file_already_present(filename, u_uuid):
    present = False
    r4 = connection_redis(4)
    user_files = r4.hgetall(u_uuid)
    if user_files is not None:
        # check if new version
        for key in user_files:
            if user_files[key] == filename:
                present = True
                break
    r4.close()
    return present


def add_file(filename, f, f_uuid, u_uuid):
    # add to db3: f_uuid = [f, f', f'', ....]
    r3 = connection_redis(3)
    r3.lpush(f_uuid, str(f))
    r3.close()

    # add to db4
    # 'u_uuid' : {
    #               'f_uuid': 'filename',
    #               'f_uuid2': 'filename2',
    #               ...
    #           }
    r4 = connection_redis(4)
    user_files = r4.hgetall(u_uuid)
    if user_files is None:
        user_files = {
            f_uuid: filename
        }
    else:
        user_files[f_uuid] = filename

    r4.hmset(u_uuid, user_files)
    r4.close()


def process_put(u_uuid, cookie):
    # Create instance of FieldStorage
    form = cgi.FieldStorage()

    file = form.getvalue('file')
    filename = form.getvalue('filename')
    print("filename:", filename)
    if file is None and filename is None:
        exit_error("no file or filename input")

    # check if already present in db4
    if file_already_present(filename, u_uuid):
        exit_error("file already present !")

    file_uuid = str(uuid.uuid4())
    print("insert file with file_uuid:", file_uuid)

    # add it: update db3 and db4
    add_file(filename, file, file_uuid, u_uuid)

    # display success
    display_success(msg="File " + filename + " with uuid" + str(file_uuid) + " uploaded !", user_uuid=u_uuid,
                    cookie=cookie)


def process_delete(u_uuid, cookie):
    # Create instance of FieldStorage
    form = cgi.FieldStorage()

    filename = form.getvalue('filename')
    print('process_delete: filename', filename)

    # get file_uuid && remove from 4
    r4 = connection_redis(4)
    user_files = r4.hgetall(u_uuid)
    if user_files is None:
        r4.close()
        exit_error("No files for this user !!")
    file_uuid = ""
    print("user_files:", user_files)
    for f in user_files:
        if user_files[f] == filename:
            file_uuid = f
    if len(file_uuid) == 0:
        r4.close()
        exit_error("File " + filename + " not present !")

    del user_files[file_uuid]
    if len(user_files.keys()) == 0:
        r4.delete(u_uuid)
    else:
        r4.hmset(u_uuid, user_files)

    # remove from 3
    r3 = connection_redis(3)
    file_history = r3.delete(file_uuid)
    if file_history is None:
        r4.close()
        r3.close()
        exit_error("Error while removing from db3")

    r3.close()
    r4.close()
    display_success(user_uuid=u_uuid, cookie=cookie, msg="Delete success !")


def process_patch(u_uuid, cookie):
    # Create instance of FieldStorage
    form = cgi.FieldStorage()

    file = form.getvalue('file')
    filename = form.getvalue('filename')
    print("filename:", filename)
    if file is None and filename is None:
        exit_error("no file or filename input")

    # get file_uuid
    r4 = connection_redis(4)
    user_files = r4.hgetall(u_uuid)
    r4.close()
    if user_files is None:
        exit_error("No Files for user " + user_uuid)
    f_uuid = ""
    for f_id in user_files:
        if user_files[f_id] == filename:
            f_uuid = f_id
            break
    if len(f_uuid) == 0:
        exit_error("File " + filename + " not present !")

    # push new version in db3
    r3 = connection_redis(3)
    r3.lpush(f_uuid, str(file))
    nb_version = r3.llen(f_uuid)
    r3.close()

    display_success(user_uuid=u_uuid, cookie=cookie, msg="Patch success ! nb_version:" + str(nb_version))


user_uuid, session_cookie = check_cookie()

# get method
method = get_method()
if len(method) == 0 and (method in ["GET", "PUT", "DELETE", "PATCH"]):
    exit_error("invalid method")
print('method:', method)

switch = {
    "GET": process_get,
    "PUT": process_put,
    "DELETE": process_delete,
    "PATCH": process_patch,
}

switch[method](user_uuid, session_cookie)
