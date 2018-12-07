#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

#include "../../include/3/bloc.h"
#include "../../include/2/mbr.h"
#include "../../include/1/drive.h"
#include "../../include/utils.h"

void usage() {
	
	printf("ERROR\n");
	printf(" usage: ./dbloc -v <volume> -n <nb_bloc>\n");
	printf(" usage: ./dbloc -v <volume> -s <bloc_start> -e <bloc_end>\n");
	exit(EXIT_FAILURE);
}

int main(int argc, char **argv) {
	
	int c,i,nb_bloc = -1;
	int start = -1,end = -1;
	unsigned int vol;
	
	while ((c = getopt (argc, argv, "v:n:s:e:V")) != -1) {
		
		switch (c) {
			
			case 'v': {
				vol = atoi(optarg);
				break;
			}
			case 'n': {
				nb_bloc = atoi(optarg);
				break;
			}
			case 's': {
				start = atoi(optarg);
				break;
			}
			case 'e': {
				end = atoi(optarg);
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
		
		printf("dbloc() enter ...\n");
		printf("  vol = %d, nb_bloc = %d\n",vol, nb_bloc);
		printf("  start = %d, end = %d\n",start, end);
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
	
	if (nb_bloc != -1) {
		
		for (i = 1; i < nb_bloc; i++) {
			
			if (verbose)
				printf("  delete bloc num %d\n", i);
			
			if (free_bloc(i))
				printf("  bloc %d deleted !\n",i);
			else {
				printf("  ERROR !!\n");
				break;
			}
		}
	}
	
	if ((start != -1) && (end != -1)) {
		
		for (i = start; i < end; i++) {
			
			if (verbose)
				printf("  delete bloc num %d", i);
			
			if (free_bloc(i) != 0)
				printf("  bloc %d deleted !\n",i);
			else {
				printf("  ERROR !!\n");
				break;
			}
		}
	}
	
	/*save_super(vol);*/
	
	if (verbose)
		printf("nbloc() exit ...\n");
	
	return 0;
}