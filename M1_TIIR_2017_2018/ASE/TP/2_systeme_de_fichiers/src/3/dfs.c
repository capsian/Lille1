#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

#include "../../include/2/mbr.h"
#include "../../include/3/bloc.h"
#include "../../include/1/drive.h"
#include "../../include/utils.h"

void usage() {

    printf("ERROR\n");
    printf(" usage: ./dfs -a\n");
    printf(" usage: ./dfs -v <vol>\n");
    
    exit(EXIT_FAILURE);
}


int main(int argc, char **argv) {

    int a = 0, v = -1, c;
	unsigned int i;

    while ((c = getopt (argc, argv, "v:aV")) != -1) {

        switch (c)
        {
            case 'a': {
                a = 1;
                break;
            }
            case 'v': {
                v = atoi(optarg);
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
	
	setup();
	load_mbr();
	
    if (a) {
        for ( i = 0; i < gMBR.nbVol; i++) {

            ls_usage(i);
        }
    }
    
    if (v != -1) {
	    ls_usage(v);
    }

    exit(EXIT_SUCCESS);
}