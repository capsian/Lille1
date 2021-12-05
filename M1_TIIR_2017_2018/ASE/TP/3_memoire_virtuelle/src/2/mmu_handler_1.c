#include <stdio.h>
#include <stdlib.h>

#include "../../include/utils.h"
#include "../../include/hardware.h"
#include "../../include/1/mmu.h"
#include "../../include/2/swap.h"

static int vmapped_page = 1;

void mmu_handler_1() {

    int faultaddr;
    struct entry_s e;

    faultaddr = _in(MMU_FAULT_ADDR);

    if (faultaddr < (int) virtual_memory || faultaddr > (int) virtual_memory + VM_SIZE - 1) {
        printf("[1] Tentative d'accès mémoire illégale : %p", (void*)faultaddr);
        exit(0);
    }

    e.access_x = e.access_w = e.access_r = 	e.active   = 1;
    
    /* restore virtual mapped page & fix physical page */
    e.vpage = vmapped_page;
    e.ppage = 1;

    /* save + forget */
    store_to_swap(vmapped_page, 1);
    _out(TLB_DEL_ENTRY, *(int *) &e);
    e.vpage = (faultaddr >> 12) & 0xFFF;

    /* load */
    _out(TLB_ADD_ENTRY, *(int *) &e);
    fetch_from_swap(e.vpage, e.ppage);
}
