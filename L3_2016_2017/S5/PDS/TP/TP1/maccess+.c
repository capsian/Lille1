#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char *argv[])
{

	char* file = argv[1];	

	/* Test number of arg */
	if ( argc < 2 )
	{
		printf("Erreur arguments\n");
		/* perror("Errno :"); */
		return 0;
	}

	/* Test if file exsist && access */
	if (access(file, F_OK) != 0)
	{
		if (errno == ENOENT)
		{
	        	printf ("Le fichier n'exsiste pas\n");
			perror("Errno :");
		}
	        else if (errno == EACCES)
		{
	        	printf ("Le fichier n'est pas accessible !\n");
			perror("Errno :");
		}
		else
		{
			perror("Errno :");
		}		        
		return 0;
	}

	/* Check parametres */
	int read = 0;
	int write = 0;
	int exec = 0;
	int verbose = 0;
	int c;

	while ((c = getopt(argc , argv, "xwrv")) != -1)
	{
		switch (c)
		{
			case 'r' : 
				read = 1;
				break;
			case 'w' :
				write = 1;
				break;
			case 'x' :
				exec = 1;
				break;
			case 'v' :
				verbose = 1;
				break;
		} 
	}

	
	/* Test parametres */
	if (read == 1)
	{
		int res = access(file,R_OK);
		if ( res == 0 )
		{
			printf("Le fichier est accessible en mode lecture\n");
		}
		else
		{
			if (verbose != 1)
				printf("Erreur\n");
			else
			{
				printf("Erreur : le fichier n'est pas accessible en mode lecture\n");
				perror("Errno :");
			}
		}
	}
	if (write == 1)
	{
		int res = access(file,W_OK);
		if ( res == 0 )
		{
			printf("Le fichier est accessible en mode écriture\n");
		}
		else
		{
			if (verbose != 1)
				printf("Erreur\n");
			else
			{
				printf("Erreur : le fichier n'est pas accessible en mode écriture\n");
				perror("Errno :");
			}
		}
	}
	if (exec == 1)
	{
		int res = access(file,X_OK);
		if ( res == 0 )
			printf("Le fichier est accessible\n");
		else
		{
			if (verbose != 1)
				printf("Erreur\n");
			else
			{
				printf("Erreur : le fichier n'est pas accessible\n");
				perror("Errno :");
			}
		}
	}

	
	return 0;
}
