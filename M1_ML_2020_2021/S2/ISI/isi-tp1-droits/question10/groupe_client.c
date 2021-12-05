#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <errno.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 4000
#define SA struct sockaddr

void func(int sockfd, char* filename) {
    FILE *f;
    char *line = NULL;
    size_t len = 2048;
    int n = 0;
    char buff[2048];

    f = fopen(filename, "r");
    if ( f != NULL) {
        while (getline(&line, &len, f) != -1) {

            printf("sending %s\n", line);

            if (send(sockfd, line, len, 0) < 0) {
                perror("send()");
                exit(errno);
            }
            if ((n = recv(sockfd, buff, 2048 - 1, 0)) < 0) {
                perror("recv()");
                exit(errno);
            }
            buff[n] = '\0';
            printf("%s\n", buff);
        }
        free(line);
        fclose(f);
    } else {
        printf("error no cmd file\n");
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char *argv[]) {
    int sockfd, connfd;
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
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = htons(PORT);

    // connect the client socket to server socket
    if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0) {
        printf("connection with the server failed...\n");
        exit(0);
    }
    else
        printf("connected to the server..\n");

    func(sockfd, argv[1]);

    // close the socket
    close(sockfd);

    return 0;
}
