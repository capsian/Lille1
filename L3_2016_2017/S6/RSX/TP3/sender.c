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

int fill(char* buffer, char* msg)
{
	int i;

	for (i=0; i<TAILLE; i++)
	{
		if (*(msg+i) == '\0')
						break;
		*(buffer+i) = *(msg+i);
	}

	return i;
}

int main()
{
	int sock;
	struct sockaddr_in addrDest;     
	struct hostent* hp; 
	char* buffer = malloc(sizeof(char) * TAILLE);
	clean(buffer);

	// creation socket
	if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
	{
		printf("Erreur création socket\n");
		exit(EXIT_FAILURE);
	}
	else
		printf("Création socket réussie\n");

	// résolution symbolique Nom => @IP
	hp = gethostbyname("localhost");

	// initialisation de l’(@IP,#Port) de destination
	addrDest.sin_family = AF_INET;
	memcpy(&addrDest.sin_addr, hp->h_addr, hp->h_length);
	addrDest.sin_port = htons(1024);

	printf("fill = %d\n",fill(buffer,"hello\0"));

	int len = sendto(sock,buffer,	8,	0, (struct sockaddr *) &addrDest, (socklen_t) sizeof (addrDest));
	if (len < 0)
	{
		printf("Erreur envoie\n");
		perror("errno :");
		exit(EXIT_FAILURE);
	}
	else
		printf("Envoi OK .... %d\n",len);


	close(sock);  
	return 0;
} 
