#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

#include "../../include/2/mbr.h"
#include "../../include/1/drive.h"

void usage() {
	
	printf("ERROR\n usage: ./mkvol -c <cylinder> -s <sector> -b <nbBlocs>\n");
	exit(EXIT_FAILURE);
}


int main(int argc, char **argv) {
	
	int sec,cyl,nbBlocs,c;
	
	while ((c = getopt (argc, argv, "c:s:b:")) != -1) {
		
		switch (c)
		{
			case 'c': {
				cyl = atoi(optarg);
				break;
			}
			case 's': {
				sec = atoi(optarg);
				break;
			}
			case 'b': {
				nbBlocs = atoi(optarg);
				break;
			}
			case '?': {
				usage();
			}
		}
	}
	
	setup();
	load_mbr();
	mkvol(nbBlocs,cyl,sec,1);
	save_mbr();
	
	exit(EXIT_SUCCESS);
}
