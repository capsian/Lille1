#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <errno.h>
#include <unistd.h>
#include <arpa/inet.h>

#define MAXLINE 2048
#define PORT 4000

int main(int argc, char *argv[]) {
    int sockfd;
    char buffer[MAXLINE];
    struct sockaddr_in     servaddr;

    // Creating socket file descriptor
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&servaddr, 0, sizeof(servaddr));

    // Filling server information
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = INADDR_ANY;

    int n, len=2048;

    FILE *f;
    char *line = NULL;
    size_t len_f = 2048;

    f = fopen(argv[1], "r");
    if ( f != NULL) {
        while (getline(&line, &len_f, f) != -1) {

            sendto(sockfd, (const char *)line, strlen(line), MSG_CONFIRM, (const struct sockaddr *) &servaddr,  sizeof(servaddr));
            printf("cmd %s, sent !\n", line);

            n = recvfrom(sockfd, (char *)buffer, MAXLINE, MSG_WAITALL, (struct sockaddr *) &servaddr, &len);
            buffer[n] = '\0';
            printf("Server : %s\n", buffer);
        }
        free(line);
        fclose(f);
    } else {
        printf("error no cmd file\n");
        exit(EXIT_FAILURE);
    }

    close(sockfd);
    return 0;
}
