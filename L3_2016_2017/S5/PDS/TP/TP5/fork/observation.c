#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/wait.h>

#define NB_PROC 4

void obs1()
{
	int i;
	
	pid_t pid;
	int status;
	
	for (i=0;i<NB_PROC;i++)
	{
		switch (pid = fork())
		{
			case -1 :
				perror("erreur fork");
				exit(EXIT_FAILURE);
			case 0 :
				while (1)
				{
					fprintf(stdout,"(pid=%d | ppid=%d) Hello ! i'm still alive !\n",getpid(),getppid());
					fflush(stdout);
					sleep(5);
				}
				exit(EXIT_SUCCESS);
		} 
	}
		
	system("echo;ps;echo");

	for (i=0;i<NB_PROC;i++)
	{
		fprintf(stdout,"Mon fils %d s'est terminé\n",wait(&status));
	}
	
	exit(EXIT_SUCCESS);
}


void obs2()
{
	int i;
	
	pid_t pid;
	int status;
	char* tmp;
	
	
	for (i=0;i<NB_PROC;i++)
	{
		switch (pid = fork())
		{
			case -1 :
				perror("erreur fork");
				exit(EXIT_FAILURE);
			case 0 :
				while (1)
				{
					fprintf(stdout,"(pid=%d | ppid=%d) Hello ! i'm still alive !\n",getpid(),getppid());
					fflush(stdout);
					sleep(5);
				}
				exit(EXIT_SUCCESS);
		} 
	}
	
	for (i=0;i<NB_PROC;i++)
	{
		if (read(STDIN_FILENO,&tmp,1))
		{
			fprintf(stdout,"J'attends la fin de mes fils ...\n");
			fflush(stdout);
			system("echo;ps;echo");
			fprintf(stdout,"Mon fils %d s'est terminé\n",wait(&status));
			fflush(stdout);
		}
	}
	
	exit(EXIT_SUCCESS);
}


int main(int argc, char** argv)
{
	/* obs1(); */
	obs2();

	return 0;
}
