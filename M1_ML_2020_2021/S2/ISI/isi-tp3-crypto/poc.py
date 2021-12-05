#!/usr/bin/python3

import socket


def client_program():
    host = "0.0.0.0"
    port = 8080

    server_socket = socket.socket()
    server_socket.bind((host, port))

    message = input(" -> ")  # take input

    while message.lower().strip() != 'bye':
        client_socket.send(message.encode())  # send message
        data = client_socket.recv(1024).decode()  # receive response

        print('Received from server: ' + data)  # show in terminal

        message = input(" -> ")  # again take input

    client_socket.close()  # close the connection


if __name__ == '__main__':
    client_program()