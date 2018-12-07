#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../include/2/mi_syscall.h"
#include "../../include/1/mmu.h"
#include "../../include/hardware.h"


static int sum(void *ptr) {

    int i;
    int sum = 0;

    for(i = 0; i < PAGE_SIZE * (PM_PAGES/2) ; i++)
        sum += ((char*)ptr)[i];

    return sum;
}

void init() {

    void* ptr;
    int res;

    ptr = virtual_memory;

    _int(16);
    memset(ptr, 1, PAGE_SIZE * (PM_PAGES/2));

    _int(17);
    memset(ptr, 3, PAGE_SIZE * (PM_PAGES/2));

    _int(16);
    res = sum(ptr);
    printf("Resultat du processus 0 : %d\n",res);

    _int(17);
    res = sum(ptr);
    printf("Resultat processus 1 : %d\n",res);

    exit(EXIT_SUCCESS);
}