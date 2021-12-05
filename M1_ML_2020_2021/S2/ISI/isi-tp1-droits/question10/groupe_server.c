#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include "check_pass.h"

#define MAX 2048
#define PORT 4000
#define SA struct sockaddr

// Function designed for chat between client and server.
void func(int sockfd) {
    char buff[MAX];
    int n;
    char delim[] = " ", *euid, *passwd;
    FILE *f;

    // infinite loop for chat
    for (;;) {
        bzero(buff, MAX);

        // read the message from client and copy it in buffer
        read(sockfd, buff, sizeof(buff));

        euid = strtok(buff, delim);
        passwd = strtok(NULL, delim);

        if (check_pass("/home/admin/passwd2", atoi(euid), passwd) == 0) {
            if (fork() == 0) {

                // drop root (change user)
                seteuid(atoi(euid));
                setegid(atoi(passwd));

                bzero(buff, MAX);
                sprintf(buff, "user %s connected", euid);
                write(sockfd, buff, sizeof(buff));

                while(1) {
                    bzero(buff, MAX);
                    read(sockfd, buff, sizeof(buff));

                    char* cmd = strtok(buff, delim);
                    char* args = strtok(NULL, delim);
                    char full_cmd[256];

                    printf("received cmd: %s %s\n", cmd, args);

                    if (strcmp(cmd, "exit") == 0) {
                        printf("Server Exit...\n");
                        break;
                    }
                    else if (strcmp(cmd, "list") == 0) {
                        strcpy(full_cmd, "ls -al ");
                    }
                    else if (strcmp(cmd, "read") == 0) {
                        strcpy(full_cmd, "cat ");
                    }
                    else {
                        printf("unkown command %s\n", cmd);
                        exit(EXIT_FAILURE);
                    }

                    strcat(full_cmd, args);
                    printf("=> cmd: %s\n", full_cmd);

                    if ((f = popen(full_cmd, "r")) == NULL){
                        printf("error popen\n");
                        exit(1);
                    }

                    bzero(buff, MAX);
                    if ((fread(buff, 1, MAX, f)) > 0) {
                        printf("popen_res: %s\n", buff);
                        if (send(sockfd, buff, strlen(buff), 0) < 0) {
                            perror("send()");
                            exit(errno);
                        }
                    }
                    pclose(f);
                }
            }
        }
    }
}

// Driver function
int main(int argc, char **argv) {
    int sockfd, connfd, len;
    struct sockaddr_in servaddr, cli;

    // socket create and verification
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        printf("socket creation failed...\n");
        exit(0);
    }
    else
        printf("Socket successfully created..\n");
    bzero(&servaddr, sizeof(servaddr));

    // assign IP, PORT
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(PORT);

    // Binding newly created socket to given IP and verification
    if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0) {
        printf("socket bind failed...\n");
        exit(0);
    }
    else
        printf("Socket successfully binded..\n");

    // Now server is ready to listen and verification
    if ((listen(sockfd, 5)) != 0) {
        printf("Listen failed...\n");
        exit(0);
    }
    else
        printf("Server listening..\n");
    len = sizeof(cli);

    // Accept the data packet from client and verification
    connfd = accept(sockfd, (SA*)&cli, &len);
    if (connfd < 0) {
        printf("server acccept failed...\n");
        exit(0);
    }
    else
        printf("server acccept the client...\n");

    // Function for chatting between client and server
    func(connfd);

    // After chatting close the socket
    close(sockfd);
}