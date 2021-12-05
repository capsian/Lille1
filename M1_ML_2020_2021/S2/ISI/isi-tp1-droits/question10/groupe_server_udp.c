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

#define MAXLINE 2048
#define PORT 4000

int main() {
    int sockfd;
    char buffer[MAXLINE];
    struct sockaddr_in servaddr, cliaddr;
    char delim[] = " ", *euid, *passwd;
    FILE *f;

    // Creating socket file descriptor
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&servaddr, 0, sizeof(servaddr));
    memset(&cliaddr, 0, sizeof(cliaddr));

    // Filling server information
    servaddr.sin_family    = AF_INET; // IPv4
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(PORT);

    // Bind the socket with the server address
    if ( bind(sockfd, (const struct sockaddr *)&servaddr,
            sizeof(servaddr)) < 0 )
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    int len, n;

    len = sizeof(cliaddr);  //len is value/resuslt

    //while(1) {
        bzero(buffer, MAXLINE);
        n = recvfrom(sockfd, (char *)buffer, MAXLINE, MSG_WAITALL, ( struct sockaddr *) &cliaddr, &len);
        buffer[n] = '\0';

        euid = strtok(buffer, delim);
        passwd = strtok(NULL, delim);
        
        uid_t uid = atoi(euid);
		gid_t gid = atoi(euid);
        
        printf("Received Client : ueid:%d geid:%d, pass:%s\n", uid, gid, passwd);

        if (check_pass("/home/admin/passwd2", atoi(euid), passwd) == 0) {
            bzero(buffer, MAXLINE);
            sprintf(buffer, "user %d:%d connected", uid, gid);
            sendto(sockfd, (const char *)buffer, strlen(buffer), MSG_CONFIRM, (const struct sockaddr *) &cliaddr, len);

            printf("father: EUID : %d - EGID : %d \n", geteuid(), getegid());
             

            //if (fork() == 0) {
                // drop root (change user)
                
                if (setegid(gid) != 0) {
                    printf("error setegid: %s\n", strerror(errno));
                    exit(EXIT_FAILURE);
                }
                
                if (seteuid(uid) != 0) {
                    printf("error seteuid: %s\n", strerror(errno));
                    exit(EXIT_FAILURE);
                }
                        

                printf("son: EUID : %d - EGID : %d \n", geteuid(), getegid());

                while(1) {

                    bzero(buffer, MAXLINE);
                    n = recvfrom(sockfd, (char *)buffer, MAXLINE, MSG_WAITALL, ( struct sockaddr *) &cliaddr, &len);
                    buffer[n] = '\0';

                    char* cmd = strtok(buffer, delim);
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

                        bzero(buffer, MAXLINE);
                        if ((fread(buffer, 1, MAXLINE, f)) > 0) {
                            printf("popen_res: %s\n", buffer);
                            sendto(sockfd, (const char *)buffer, strlen(buffer), MSG_CONFIRM, (const struct sockaddr *) &cliaddr, len);
                        }
                        pclose(f);
                }
            //}
        //}
    }

    return 0;
}
