#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h> 
#include <netdb.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define TAILLE 512

void clean(char* buffer)
{
	int i;

	for (i=0; i<TAILLE; i++)
	{
		*(buffer+i) = '\0';
	}

	return;
}

void display(char* msg)
{
	int i;
	
	for (i=0; i<TAILLE; i++)
	{
		if ( *(msg+i) == '\0')
			break;
		else
			printf("%c",*(msg+i));
	}
	printf("\n");
	return;
}

int main()
{
	int sock;
	struct sockaddr_in sin;
	struct sockaddr_in from;
	char *buffer = malloc(sizeof(char) * TAILLE);
	clean(buffer);
	
	// creation socket
	if ( (sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
	{
		printf("Erreur création socket\n");
		exit(EXIT_FAILURE);
	}
	else
		printf("Création socket réussie\n");


	sin.sin_addr.s_addr = INADDR_ANY;
	sin.sin_family = AF_INET;
	sin.sin_port = htons(1024);


	// liaison
	if ( bind (sock, (struct sockaddr *) &sin, sizeof(struct sockaddr_in)) < 0)
	{
		printf("Erreur liaison socket\n");
		perror("errno :");
		exit(EXIT_FAILURE);
	}
	else
		printf("liaison réussie\n");


	struct sockaddr_storage sender;
	socklen_t sendsize = sizeof(sender);
	bzero(&sender, sizeof(sender));

	
	// recv
	int len = recvfrom(sock, buffer, 8, 0, (struct sockaddr*)&from, &sendsize);
	if ( len < 0)
	{
		printf("Erreur réception\n");
		perror("errno :");
		exit(EXIT_FAILURE);
	}
	else
	{
		printf("longueur message : %d\nmessage : \n",len);
		display(buffer);
	}

	
	close(sock); 
	return 0;
} 
