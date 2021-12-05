#include <stdio.h>
#include <stdlib.h>

#include "../include/hardware.h"
#include "../include/utils.h"
#include "../include/1/mmu.h"

void empty_it() {
	return;
}

void setup() {
	
	int i;
	
	/* init hardware */
	if(init_hardware(HWCONFIG) == 0) {
		fprintf(stderr, "Error in hardware initialization\n");
		exit(EXIT_FAILURE);
	}
	
	for(i=0; i<16; i++)
		IRQVECTOR[i] = empty_it;
	
	/* Allows all IT */
	_mask(1);
}