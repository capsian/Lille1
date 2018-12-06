#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

#include "../../include/3/bloc.h"
#include "../../include/2/mbr.h"
#include "../../include/1/drive.h"
#include "../../include/utils.h"

void usage() {

    printf("ERROR\n usage: ./mknfs -v <volume> -n <name> -s <serial>\n");
    exit(EXIT_FAILURE);
}

int main(int argc, char **argv) {

    int c,serial;
    unsigned int vol;
    char name[32];

    while ((c = getopt (argc, argv, "v:n:s:V")) != -1) {

        switch (c) {

            case 'v': {
                vol = atoi(optarg);
                break;
            }
            case 's': {
                serial = atoi(optarg);
                break;
            }
            case 'n': {
                strcpy(name,optarg);
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
        
        printf("mknfs() enter ...\n");
        printf("  s = %d, vol = %d, name = %s\n",serial,vol,name);
        
    }
    
    setup();
    
    if (verbose) {
        
        printf(" setup() ... DONE!\n");
    }
    
    load_mbr();
    
    if (verbose) {
    
        printf(" load_mbr() ... DONE!\n");
    }
    
    init_super(vol, serial, name);
	save_super();
	save_mbr();
    
    if (verbose) {
        
        printf("mknfs() exit ...\n");
    }
    
    return 0;
}