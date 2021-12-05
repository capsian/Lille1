#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

#include "../../include/3/bloc.h"
#include "../../include/2/mbr.h"
#include "../../include/1/drive.h"
#include "../../include/utils.h"

void usage() {
	
	printf("ERROR\n usage: ./nbloc -v <volume> -n <nb_bloc>\n");
	exit(EXIT_FAILURE);
}

int main(int argc, char **argv) {
	
	int c,i,nb_bloc;
	unsigned int vol;
	int tmp = -1;
	
	while ((c = getopt (argc, argv, "v:n:V")) != -1) {
		
		switch (c) {
			
			case 'v': {
				vol = atoi(optarg);
				break;
			}
			case 'n': {
				nb_bloc = atoi(optarg);
				break;
			}
			case 'V': {
				set_verbose(1);
				break;
			}
			
			case '?':
			default:
				usage();
		}
	}
	
	if (verbose) {
		
		printf("nbloc() enter ...\n");
		printf("  vol = %d, nb_bloc = %d\n",vol, nb_bloc);
	}
	
	setup();
	
	if (verbose)
		printf(" setup() ... DONE!\n");
	
	load_mbr();
	
	if (verbose)
		printf(" load_mbr() ... DONE!\n");
	
	load_super(vol);
	
	if (verbose)
		printf(" load_super(%d) ... DONE!\n",vol);
	
	for (i = 0; i < nb_bloc; i++) {
		
		if (verbose)
			printf("  construct bloc num %d",i);
		
		if ( (tmp = new_bloc()) )
			printf("  new_bloc_num = %d\n",tmp);
		else {
			printf("  MAX BLOC REACHED !!\n");
			break;
		}
	}
	
	save_super(vol);
	
	if (verbose)
		printf("nbloc() exit ...\n");
	
	return 0;
}