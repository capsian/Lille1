#include <stdio.h>
#include <stdlib.h>

#include "../../include/hardware.h"
#include "../../include/1/mmu.h"

struct entry_s e;
int current_process;

void init_entry() {

	e.rfu = 0;
	e.vpage = 0;
	e.ppage = 0;
	e.access_x = 0;
	e.access_w = 0;
	e.access_r = 0;
	e.active = 0;
}

int ppage_of_vpage(int process, unsigned int vpage) {

	return (vpage < 127) ? ((int)vpage + 0x80 * process) + 1 : -1;
}

void mmu_handler() {

	int faultaddr = _in(MMU_FAULT_ADDR);

	if (faultaddr < (int) virtual_memory || faultaddr > (int) virtual_memory + VM_SIZE - 1) {
		printf("[1] Tentative d'accès mémoire illégale : %p", (void*)faultaddr);
		exit(0);
	}

	e.vpage = (faultaddr >> 12) & 0xFFF;

	if ((e.ppage = ppage_of_vpage(current_process, e.vpage)) == -1) {
		printf("[2] Tentative d'accès mémoire illégale : %p", (void*)faultaddr);
		exit(1);
	}

	e.access_x = e.access_w = e.access_r = 	e.active   = 1;

	_out(TLB_ADD_ENTRY, *(int *) &e);
}
