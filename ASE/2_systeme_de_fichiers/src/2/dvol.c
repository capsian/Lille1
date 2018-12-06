#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

#include "../../include/2/mbr.h"
#include "../../include/1/drive.h"

void usage() {

	printf("ERROR\n usage: ./dvol -a\n usage: ./dvol -v <vol_num>");
	exit(EXIT_FAILURE);
}


int main(int argc, char **argv) {

	int c;
    unsigned int vol;

	setup();
	load_mbr();

	while ((c = getopt (argc, argv, "av:")) != -1) {

		switch (c)
		{
			case 'a': {
				ls_vol();
				break;
			}
			case 'v': {
				vol = atoi(optarg);
                ls_specific_vol(vol);
				break;
			}
			case '?':
			default:
				usage();
		}
	}
	
	exit(EXIT_SUCCESS);
}
