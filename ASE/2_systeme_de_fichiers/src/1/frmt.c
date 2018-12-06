#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>

#include "../../include/utils.h"
#include "../../include/1/drive.h"

void usage() {
	
	printf("ERROR\n usage: ./frmt <cyl> <sec> || ./frmt -a || ./frmt -r\n");
	exit(EXIT_FAILURE);
}

void format_all() {
	
	unsigned int i,j;
	
	for (i = 0; i < HDA_MAXCYLINDER; i++)
		for (j = 0; j < HDA_MAXSECTOR; j++)
			format_sector(i,j,0);
}

void format_all_reverse() {
	
	unsigned int i,j;
	
	for (i = HDA_MAXCYLINDER - 1; i > 0; i--)
		for (j = HDA_MAXSECTOR - 1; j > 0; j--)
			format_sector(i,j,0);
}

int main(int argc, char **argv) {
	
	int c;
	int cyl,sec;
	
	setup();

	while ((c = getopt (argc, argv, "ar")) != -1) {
	
		switch (c)
		{
			case 'a': {
				format_all();

				exit(EXIT_SUCCESS);
			}
			case 'r': {
				format_all_reverse();

				exit(EXIT_SUCCESS);
			}
			case '?': {
				usage();
			}
		}
	}
	
	if (argc < 2) {
		usage();
	}
	
	cyl = strtol(argv[1],NULL,10);
	sec = strtol(argv[2],NULL,10);
	
	check_input(cyl,sec);
	
	format_sector(cyl,sec,0);

	exit(EXIT_SUCCESS);
}
