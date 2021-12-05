#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <time.h>
#include <pthread.h>

#define TIME_MAX 2

char *hostname;
char * buffer;
int portno;
time_t start_time;

void start_timer() {
    start_time = time(NULL);
}

double get_elapsed_time() {
    return difftime(time(NULL), start_time);
}

/*
 * error - wrapper for perror
 */
void error(char *msg) {
    perror(msg);
    exit(0);
}


char* gen(unsigned long long int length) {

    char* res = malloc(sizeof(char) * length);
    memset(res,1,length);
    return res;
}

int multi_connect() {

    int sockfd;
    struct sockaddr_in serveraddr;
    struct hostent *server;

    /* socket: create the socket */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        error("ERROR opening socket");

    /* gethostbyname: get the server's DNS entry */
    server = gethostbyname(hostname);
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host as %s\n", hostname);
        exit(0);
    }

    /* build the server's Internet address */
    bzero((char *) &serveraddr, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    bcopy((char *)server->h_addr,
          (char *)&serveraddr.sin_addr.s_addr, server->h_length);
    serveraddr.sin_port = htons(portno);

    /* connect: create a connection with the server */
    if (connect(sockfd, (struct sockaddr*) &serveraddr, sizeof(serveraddr)) < 0) {
      exit(EXIT_FAILURE);
      error("ERROR connecting");
    }

    return sockfd;
}

void *send_n(void * lenght) {

    int n = *(int *)lenght;
    int nboctets = 0;
    while(get_elapsed_time() < TIME_MAX){

        int sockfd = multi_connect();
        /*send data */
        nboctets += write(sockfd, buffer, n);

        if (n < 0)
            error("ERROR writing to socket");
        close(sockfd);
    }

    return (void*)nboctets;
}

int main(int argc, char **argv) {

    int  nb_t,length;
    pthread_t* thread_id;
    int nb_oct_per_th;
    int nb_oct_total = 0;

    /* check command line arguments */
    if (argc != 5) {
        fprintf(stderr,"usage: %s <hostname> <port> <length>\n", argv[0]);
        exit(0);
    }
    hostname = argv[1];
    portno = atoi(argv[2]);
    length = atoi(argv[3]);
    nb_t   = atoi(argv[4]);
    buffer = gen(length);
    /* MULTITHREAD */
    if (nb_t > 1) {

        thread_id = malloc(sizeof(pthread_t) * nb_t);
        start_timer();
        /* MULTITHREAD */
        for (int i =0; i<nb_t; i++) {
            if (pthread_create(&thread_id[i], NULL, send_n, (void *) &length) < 0) {
                perror("could not create thread");
                exit(EXIT_FAILURE);
            }
        }

        /* WAITING THREADS */
        for (int i =0; i<nb_t; i++) {
            pthread_join(thread_id[i], &nb_oct_per_th);
            nb_oct_total += nb_oct_per_th;
        }

    }
    /* SINGLE THREAD */
    else {
        start_timer();
        nb_oct_total = send_n(&length);

        if (nb_oct_total < 0)
            error("ERROR writing to socket");
    }

    printf("%d\n",nb_oct_total/2);
    free(buffer);
    
    return 0;
}
