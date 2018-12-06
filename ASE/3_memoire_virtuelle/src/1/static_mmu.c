#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../include/hardware.h"
#include "../../include/utils.h"
#include "../../include/1/mmu.h"

struct entry_s e;
int current_process;

static int sum(void* ptr) {

    int i;
    int sum = 0;

    for(i = 0; i < PAGE_SIZE * ((PM_PAGES/2)-2) ; i++)
        sum += ((char*) ptr) [i];

    return sum;
}

static void switch_to_process0 (void) {
	
	printf("switch_to_process0() enter ...\n");

	current_process = 0;
    _out(MMU_CMD, MMU_RESET);
	
	printf("switch_to_process0() exit ...\n");
	return;
}

static void switch_to_process1(void) {
	
	printf("switch_to_process1() enter ...\n");
 
	current_process = 1;
    _out(MMU_CMD, MMU_RESET);
	
	printf("switch_to_process1() exit ...\n");
	return;
}

int main(/*int argc, char** argv*/) {

    void* ptr;
    int res;
    
	/* init hardware + IRQVECTOR */
	setup();
    
    IRQVECTOR[16] = switch_to_process0;
	IRQVECTOR[17] = switch_to_process1;
	IRQVECTOR[MMU_IRQ] = mmu_handler;
    /* user mode + allow all inter */
	_mask(0x1001);

    /*printf("SEG.FAULT !!\n");
    IRQVECTOR[MMU_IRQ] = mmu_handler;*/

    ptr = virtual_memory;

    /*printf("PAGE_SIZE * (PM_PAGES/2) = %d\n",(PM_PAGES/2));*/
	
    _int(16);
    memset(ptr, 1, PAGE_SIZE * ((PM_PAGES/2)-2));

    _int(17);
    memset(ptr, 3, PAGE_SIZE * ((PM_PAGES/2)-2));

    _int(16);
    res = sum(ptr);
    printf("Resultat du processus 0 : %d\n",res);

    _int(17);
    res = sum(ptr);
    printf("Resultat processus 1 : %d\n",res);

    exit(EXIT_SUCCESS);
}