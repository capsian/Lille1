#include <stdio.h>
#include <stdlib.h>

#include "../../include/utils.h"
#include "../../include/hardware.h"
#include "../../include/1/mmu.h"
#include "../../include/2/swap.h"

extern void user_process();
static unsigned int next_fifo = 1;

struct vmm_s {
    int is_mapped:1;
    int ppage:8;
};

struct pmm_s {
    int is_mapped:1;
    int vpage:12;
};

struct vmm_s VM_mapping[VM_PAGES];
struct pmm_s PM_mapping[PM_PAGES];

void mmu_handler_2() {

    struct entry_s e;
    int faultaddr, vpage;

    faultaddr = _in(MMU_FAULT_ADDR);
    if(faultaddr < (int)virtual_memory || faultaddr > ((int)virtual_memory + VM_SIZE -1)){
        printf("tentative d’accès illégal à l’adresse %p\n", (void *)faultaddr);
        exit(EXIT_FAILURE);
    }

    vpage = (faultaddr >> 12) & 0x00000FFF;
    if (VM_mapping[vpage].is_mapped) {

        /*Just add TLB*/
        e.vpage = vpage;
        e.ppage = VM_mapping[vpage].ppage;
        e.access_x = 1;
        e.access_w = 1;
        e.access_r = 1;
        e.active = 1;
        _out(TLB_ADD_ENTRY,*(int *)&e);
    }else{

        /*La place est prise,Virer une ppage et stock dans swap*/
        if(PM_mapping[next_fifo].is_mapped){
            /*printf("Need to swap %d\n", next_fifo);*/
            store_to_swap(PM_mapping[next_fifo].vpage,next_fifo);
            e.vpage = PM_mapping[next_fifo].vpage;
            e.ppage = next_fifo;
            VM_mapping[e.vpage].is_mapped = 0;
            /*Remove son map tlb*/
            _out(TLB_DEL_ENTRY,*(int *)&e);
            e.vpage = vpage;
            /*Load swap la vpage*/
            fetch_from_swap(e.vpage,e.ppage);
            PM_mapping[next_fifo].vpage = vpage;
            VM_mapping[vpage].is_mapped = 1;
            VM_mapping[vpage].ppage = e.ppage;
            /*Add tlb*/
            e.access_x = 1;
            e.access_w = 1;
            e.access_r = 1;
            e.active = 1;
            /*printf("PPAGE : %d\n", e.ppage );*/
            _out(TLB_ADD_ENTRY,*(int *)&e);
        }else{
            /*Il reste de la place dans la partie physique pas de swap
            printf("No need to swap\n");*/
            PM_mapping[next_fifo].is_mapped = 1;
            PM_mapping[next_fifo].vpage = vpage;
            VM_mapping[vpage].is_mapped = 1;
            VM_mapping[vpage].ppage = next_fifo;
            e.vpage = vpage;
            e.ppage = next_fifo;
            e.access_x = 1;
            e.access_w = 1;
            e.access_r = 1;
            e.active = 1;

            _out(TLB_ADD_ENTRY,*(int *)&e);
        }
        /*Update next ppage to remove*/

        next_fifo++;
        if(next_fifo == PM_PAGES)
            next_fifo = 1;
        /*printf("Fin de mmu %d\n", next_fifo);*/
    }
}

int main(/*int argc, char **argv*/) {

    /* init hardware + IRQVECTOR */
    setup();

    IRQVECTOR[MMU_IRQ] = mmu_handler_2;
    _mask(0x1001);

    /* user mode */
    user_process();
    return 0;
}

