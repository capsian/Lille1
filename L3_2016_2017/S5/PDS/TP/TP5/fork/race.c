#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/wait.h>

#define Z 100000000


void race()
{
	int i;
	int k;
	pid_t pid;
	int status;
	
	int* res=NULL;
	res = malloc(sizeof(int)*10);
	
	for (i=0;i<10;i++)
	{
		switch (pid = fork())
		{
			case -1 :
				perror("erreur fork");
				exit(EXIT_FAILURE);
			case 0 :
				fprintf(stdout,"(ppid=%d|pid=%d) se lance dans la course !\n",getppid(),getpid());
				fflush(stdout);
				for (k=0;k<Z;k++);
				exit(EXIT_SUCCESS);
		} 
	}
	
	for (i=0;i<10;i++)
	{
		*(res+i) = wait(&status);
	}
	
	for (i=0;i<10;i++)
	{
		fprintf(stdout,"%d : pid = %d\n",i,*(res+i));
		fflush(stdout);
	}
	
	free(res);
	return;
}

int main(int argc, char** argv)
{
	race();
	return 0;
}
