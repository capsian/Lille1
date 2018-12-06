#include <stdlib.h>
#include <stdio.h>

#include "../../include/utils.h"
#include "../../include/1/drive.h"

#define BUFFER_SIZE 256
unsigned char buffer[BUFFER_SIZE];

void usage() {
	
	printf("ERROR\n usage: ./dmps cyl sec\n ./dmps cyl sec 1 <for verbose>");
	exit(EXIT_FAILURE);
}

int main(int argc, char **argv) {
	
	int cyl, sec;
	
	if (argc < 2) {
		usage();
	}
	
	if (argc == 3)
		set_verbose (1);
		
	if (verbose)
		printf("Setup .... (mkhd) ");
	
	setup();
	
	if (verbose)
		printf(" DONE !\n");
	
	cyl = strtol(argv[1],NULL,10);
	sec = strtol(argv[2],NULL,10);
	
	check_input(cyl,sec);
	
	if (verbose)
		printf("Reading .... ");
	read_sector(cyl,sec,buffer);
	
	if (verbose)
		printf(" DONE !\n");
	if (verbose)
		printf("Display:\n");
	
	display_buffer(buffer);
	
	if (verbose)
		printf("Exit .....\n");
	
	exit(EXIT_SUCCESS);
}
