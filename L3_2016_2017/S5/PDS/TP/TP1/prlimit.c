#include <unistd.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	printf("NAME_MAX : %d \nPATH_MAX:%d\n",NAME_MAX,PATH_MAX);
	return 0;
}
