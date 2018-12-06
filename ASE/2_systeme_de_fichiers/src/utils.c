#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include "../include/utils.h"
#include "../include/1/drive.h"
#include "../include/2/mbr.h"
#include "../include/3/bloc.h"

static unsigned int i, j;
unsigned int verbose = 0;

void set_verbose(unsigned int v) { verbose = v; }

void empty_it() { return; }

void check_input(int cyl, int sec) {
	
	if ((cyl > 15) || (cyl < 0)) {
		printf("ERROR\n invalid cyl\n");
		exit(EXIT_FAILURE);
	}
	
	if ((sec > 15) || (sec < 0)) {
		printf("ERROR\n invalid sec\n");
		exit(EXIT_FAILURE);
	}
}

void clean_buffer(unsigned char* buffer) {
	
	for (i = 0; i < HDA_SECTORSIZE; i++) {
		buffer[i] = 0;
	}
}

void set_buffer(unsigned char* buffer, char value) {
	
	for (i = 0; i < HDA_SECTORSIZE; i++) {
		buffer[i] = value;
	}
}

void display_buffer(unsigned char* buffer) {
	
	for (i = 0; i < HDA_SECTORSIZE; i+=16) {
		printf("%03d : ",i);
		for (j = 0; j < 16; j++) {
			printf(" %02x",buffer[i+j]);
		}
		printf("\n");
	}
}

void mount(unsigned int vol) {
	current_vol = vol;
	setup();
	load_mbr();
	load_super(current_vol);
}

void umount() {
	save_super();
}