#include <stdio.h>
#include <stdlib.h>

#include "../../include/hardware.h"
#include "../../include/utils.h"
#include "../../include/1/mmu.h"

#define ADDRESS &virtual_memory

static void mmuhandler() {
	
	printf("tentative d’acces illégal à l’adresse %p\n", (void*) _in(MMU_FAULT_ADDR));
}

int main(/*int argc, char** argv*/) {
	
	char* ptr;

	/* init hardware */
	setup();
	
	IRQVECTOR[MMU_IRQ] = mmuhandler;
	_mask(0x1001);
	/*IRQVECTOR[MMU_IRQ] = mmuhandler;*/
	
	ptr = ADDRESS;
	*ptr = 'c';

	printf("test_mmu  ...  DONE !\n");
	printf(" ptr = %p\n",ptr);
	printf(" *ptr = %d\n",*ptr);

	return 0;
}