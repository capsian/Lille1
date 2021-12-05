#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "server.h"


int create_a_socket(char *adr, int port, int bind_or_select) {
    struct sockaddr_in my_addr;
    int mysocket;
    int res_bind;

    mysocket = socket(AF_INET, SOCK_STREAM, 0);
    if (mysocket == -1) {
        fprintf(stderr, "La socket n'a pu être créer\n");
        exit(EXIT_FAILURE);
    }
    my_addr.sin_family = AF_INET;
    my_addr.sin_port = htons(port);
    my_addr.sin_addr.s_addr = inet_addr(adr);
    bzero(&(my_addr.sin_zero), 8);


    if (bind_or_select) {
        //BIND
        res_bind = bind(mysocket, (struct sockaddr *) &my_addr, sizeof(struct sockaddr));
        if (res_bind == -1) {
            fprintf(stderr, "Le port est déjà attribuer\n");
            exit(EXIT_FAILURE);
        }

    } else {
        //SELECT

    }
    listen(mysocket, BACKLOG);
    return mysocket;
}

void *connection_handler(void *socket_desc) {
    char* buffer = malloc(MTU);
    int sclient = (int) socket_desc;
    int i;
    while ((i = recv(sclient, buffer, MTU, 0)));
        //printf("Received %d octets on connection : %d\n", i, sclient);
    close(sclient);
    free(buffer);
    //printf("Client disconnected\n");
    return NULL;
}

void init_server(char *adr, int port, int bind_or_select) {
    struct sockaddr_in client;
    int * clientSock;
    pthread_t clientThread;
    int mysocket, c;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    c = sizeof(struct sockaddr_in);
    mysocket = create_a_socket(adr, port, bind_or_select);
    while ((clientSock = accept(mysocket, (struct sockaddr *) &client, (socklen_t *) &c))) {

        //puts("Connection accepted");

        if (pthread_create(&clientThread, &attr, connection_handler, (void *) clientSock) < 0) {
            perror("could not create thread");
            return;
        }
      //  pthread_join(clientThread,NULL);

      //  puts("Handler assigned");
    }
}

void usage() {
    printf("./server <ipaddr> <port> <bind_or_select>\n");
}

int main(int argc, char *argv[]) {
    if (argc <= 3) {
        usage();
        return 0;
    }
    int port = atoi(argv[2]);
    int bind_or_select = atoi(argv[3]);
    init_server(argv[1], port, bind_or_select);
    return 0;
}
