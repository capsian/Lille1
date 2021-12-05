#!/usr/bin/python3

import subprocess


def to_hex(str):
    return


def xor(str1, str2):
    str1 = int(str1, base=16)
    str2 = int(str2, base=16)
    return hex(str1 ^ str2)[2:]  # remove 0x


def write(file, str):
    f = open(file, "w")
    f.write(str)
    f.close()


def write2(file, str):
    f = open(file, "a")
    f.write(str)
    f.close()


def read(file):
    try:
        with open(file) as f:
            content = f.readlines()
    except IOError:
        print("error while opening " + str(file))
        return ''
    return content[0].strip()


def init():
    print("Gen M1", end='')
    output = subprocess.run(['openssl', 'rand', '-hex', '32'], text=True, capture_output=True)
    M1 = output.stdout.strip()
    write('server/M1.key', M1)
    print(".... Done !")

    print("Gen M2", end='')
    output = subprocess.run(['openssl', 'rand', '-hex', '32'], text=True, capture_output=True)
    M2 = output.stdout.strip()
    write('server/M2.key', M2)
    print(".... Done !")

    print("Gen M", end='')
    M = xor(M1, M2)
    write('server/M.key', M)
    print(".... Done !")

    print("Gen Mask1 for USER1", end='')
    output = subprocess.run(['openssl', 'rand', '-hex', '32'], text=True, capture_output=True)
    Mask1 = output.stdout.strip()
    write('server/masks/USER1.mask', Mask1)
    print(".... Done !")

    print("Gen Mask2 for REP1", end='')
    output = subprocess.run(['openssl', 'rand', '-hex', '32'], text=True, capture_output=True)
    Mask2 = output.stdout.strip()
    write('server/masks/REP1.mask', Mask2)
    print(".... Done !")

    print("Gen Mask3 for USER2", end='')
    output = subprocess.run(['openssl', 'rand', '-hex', '32'], text=True, capture_output=True)
    Mask3 = output.stdout.strip()
    write('server/masks/USER2.mask', Mask3)
    print(".... Done !")

    print("Gen Mask3 for REP2", end='')
    output = subprocess.run(['openssl', 'rand', '-hex', '32'], text=True, capture_output=True)
    Mask4 = output.stdout.strip()
    write('server/masks/REP2.mask', Mask4)
    print(".... Done !")

    print("Gen Key1 for USER1", end='')
    Key1 = xor(M1, Mask1)
    write('users/USER1.key', Key1)
    print(".... Done !")

    print("Gen Key2 for REP1", end='')
    Key2 = xor(M1, Mask2)
    write('users/REP1.key', Key2)
    print(".... Done !")

    print("Gen Key3 for USER2", end='')
    Key3 = xor(M2, Mask3)
    write('users/USER2.key', Key3)
    print(".... Done !")

    print("Gen Key4 for REP2", end='')
    Key4 = xor(M2, Mask4)
    write('users/REP2.key', Key4)
    print(".... Done !")

    print("Encoding DB with key M: " + str(M))
    args = ['openssl', 'enc', '-aes-256-cbc', '-in', 'server/db/init.txt', '-out', 'server/db/data.csv.enc', '-k', M,
            '-pbkdf2']
    output = subprocess.run(args, text=True, capture_output=True)
    if output.returncode != 0:
        print("error while encoding ....")


if __name__ == '__main__':
    init()
