#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/wait.h>

typedef int (*func_t) (int);

static int f(int k) 
{
    return k;
}

func_t* create_tab_func (int n)
{
	int i;
	func_t *tab=NULL;
	tab = malloc(sizeof(func_t)*n);
	assert(tab != NULL);
	
	for (i=0;i<n;i++)
	{
		*(tab+i) = f; 
	}
	
	return tab;
}

int* build_tab_args(char* argv[], int n)
{
	int* tab=NULL;
	int i;
	tab = malloc(sizeof(int)*n);
	assert(tab != NULL);
	
	for (i=0;i<n;i++)
	{
		*(tab+i) = atoi(argv[i]);
	}
	
	return tab;
}

void init_tab_ok (int* tab, int n)
{
	int i;
	
	for (i=0;i<n;i++)
	{
		*(tab+i) = -1;
	}
}

int conjunction(int* tab, int n)
{
	int i;
	
	for (i=0;i<n;i++)
	{
		if (*(tab+i) != 0)
			return 0;
	}
	
	return 1;
}

int multif (func_t* f, int* args, int n)
{
	int i;
	int result;
	
	pid_t pid;
	int status;
	
	int* tab_ok;
	tab_ok = malloc(sizeof(int)*n);
	assert(tab_ok != NULL);
	init_tab_ok(tab_ok,n);
	
	fprintf(stdout,"(ppid=%d | pid=%d) Im the father\n",getppid(),getpid());
	fflush(stdout);
	
	
	for (i=0;i<n;i++)
	{
		switch (pid = fork())
		{
			case -1 :
				perror("erreur fork");
				exit(EXIT_FAILURE);
			case 0 :
				result = f[i](args[i]);
				fprintf(stdout,"(pid=%d | ppid=%d) I print %d\n",getpid(),getppid(),result);
				fflush(stdout);
				exit(EXIT_SUCCESS);
			default :
				waitpid(pid,&status,0);
				*(tab_ok+i) = WEXITSTATUS(status);
		} 
	}
	
	if (conjunction(tab_ok,n))
	{
		fprintf(stdout,"[CONJ] Im a good father, all my sons finished their work\n");
		fflush(stdout);
		free(tab_ok);
		return 1;
	}	
	else
	{
		fprintf(stdout,"[CONJ] Im not your father :D\n");
		fflush(stdout);
		free(tab_ok);
		return 0;
	}
}

int main(int argc, char* argv[])
{
	func_t* tab_f=NULL;
	int* tab_arg=NULL;
	
	tab_f = create_tab_func (argc-1);
	tab_arg = build_tab_args(argv,argc);
	
	assert(argc>1);
	
	multif(tab_f,tab_arg+1,argc-1);
	
	free(tab_f);
	free(tab_arg);
	
	return 1;
}
