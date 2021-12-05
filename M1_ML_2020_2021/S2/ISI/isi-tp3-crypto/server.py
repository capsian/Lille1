#!/usr/bin/python3

import socket
import init
import subprocess
import os

authenticated = False
m, m1, m2 = '', '', ''


def decrypt():
    if not authenticated:
        print("Your are note authenticated !")
        return
    args = ['openssl', 'enc', '-aes-256-cbc', '-d', '-in', 'server/db/data.csv.enc', '-k', m, '-pbkdf2']
    output = subprocess.run(args, text=True, capture_output=True)
    if output.returncode != 0:
        print("add_card error: " + str(output))
        return
    return output.stdout


def encrypt(data):
    if not authenticated:
        print("Your are note authenticated !")
        return
    print("encrypt: " + str(data))
    ret = os.system('echo ' + data + ' | openssl enc -aes-256-cbc -out server/db/data.csv.enc -k ' + m + ' -pbkdf2')
    if ret != 0:
        print("error while encrypt")
        return


def server_program():
    host = "0.0.0.0"
    port = 8080

    server_socket = socket.socket()
    server_socket.bind((host, port))

    print("listening on %s:%s" % (host, port))
    server_socket.listen(2)
    conn, address = server_socket.accept()
    print("Connection from: " + str(address))
    while True:
        # receive data stream. it won't accept data packet greater than 1024 bytes
        data = conn.recv(1024).decode()
        if not data:
            # if data is not received break
            break
        print("from connected user: " + str(data))
        data = input(' -> ')
        conn.send(data.encode())  # send data to the client

    conn.close()  # close the connection


def auth(user1, pwd1, user2, pwd2):
    global m, m1, m2
    u1_mask = init.read('server/masks/' + str(user1) + '.mask')
    u2_mask = init.read('server/masks/' + str(user2) + '.mask')
    if u1_mask == '':
        print("No mask found for " + str(user1))
        return
    if u2_mask == '':
        print("No mask found for " + str(user2))
        return
    m1 = init.xor(u1_mask, pwd1)
    m2 = init.xor(u2_mask, pwd2)
    m = init.xor(m1, m2)
    args = ['openssl', 'enc', '-aes-256-cbc', '-d', '-in', 'server/db/data.csv.enc', '-k', m, '-pbkdf2']
    output = subprocess.run(args, text=True, capture_output=True)
    if output.returncode != 0:
        print("auth error: " + str(output))
        return
    global authenticated
    authenticated = True
    print(user1 + ", " + user2 + " Authenticated !")
    return True


def add_card(name, card_num):
    encrypt(decrypt().strip() + "_" + name + "-" + card_num)


def del_card(name):
    data = decrypt().strip()
    records = data.split("_")
    new = ''
    for r in records:
        n, c = r.split('-')
        if name != n:
            new += n + '-' + c + "_"
        else:
            print("card of " + name + " deleted !")

    encrypt(new[:-1])  # remove the last _


def get_card(name):
    data = decrypt().strip()
    records = data.split("_")
    for r in records:
        n, c = r.split('-')
        if name == n:
            print(n, c)


def rm_user(user_to_del, u1, p1, u2, p2, u3, p3):
    u1_mask = init.read("server/masks/" + u1 + ".mask")
    u2_mask = init.read("server/masks/" + u2 + ".mask")
    u3_mask = init.read("server/masks/" + u3 + ".mask")
    del_mask = init.read("server/masks/" + user_to_del + ".mask")

    if u1_mask == '':
        print("rm_user mask of " + u1 + " not found !")
        return
    if u2_mask == '':
        print("rm_user mask of " + u2 + " not found !")
        return
    if u3_mask == '':
        print("rm_user mask of " + u3 + " not found !")
        return
    if del_mask == '':
        print("rm_user mask of " + user_to_del + " not found !")
        return

    if not auth(u1, p1, u2, p2):
        print("rm_user auth error1")
    if not auth(u1, p1, u3, p3):
        print("rm_user auth error2")

    print("TODO remove mask")


if __name__ == '__main__':
    u1, p1 = 'REP1', '877d34f0750e065d757fdfdd0a89346e2a22e9bdf8bf3c1d1f818cc18cebcce0'
    u2, p2 = 'USER2', 'c76ac0eb2378a34bfd2d5731d8a3051fb90b7a466b330250f9098d39cfb9c378'
    u3, p3 = 'REP2', 'c192d561b1589aa959392cd581c450f9558729182cde3ca03925717d3d344d6c'
    auth(u1, p1, u2, p2)
    rm_user('USER1', 'REP1', p1, 'USER2', p2, 'REP2', p3)
