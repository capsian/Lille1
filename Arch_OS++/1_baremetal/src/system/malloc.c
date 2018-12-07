#include <setup.h>
#include "system/malloc.h"
#include "drivers/screen.h"

struct free_block_s blocks[NB_BLOCKS];
int index = 0;
char memory[16*Mo];
char * top_heap = memory;

void *malloc(int size) {

    char *tmp = top_heap;

    /* CHECK LIMITS */
    if (((top_heap + size) < (memory + (16 * Mo))) && index < NB_BLOCKS) {

        if (VERBOSE) {
            //puts("malloc() 1: last_top_heap = "); puthex( (int) top_heap); puts(" | size = "); put_number(size);
        }

        top_heap += size + 1;

        if (VERBOSE) {
            //puts("new_top_heap = "); puthex( (int) top_heap); puts(" \n");
        }

        struct free_block_s new;

        new.size = size;
        new.base_address = tmp;
        new.free = 0;
        blocks[index++] = new;

        return tmp;
    }
    //Un bloc libre disponible pour cette taille ?
    else {

        if (VERBOSE) {
            //puts("malloc() 2\n");
        }

        for (int i = 0; i < index; i++) {
            if (blocks[i].size >= size && blocks[i].free)
                return blocks[i].base_address;
        }
    }

    return 0;
}

void free(void *adr) {

    for (int i = 0; i < index; i++) {

        if (blocks[i].base_address == adr && !blocks[i].free) {
            blocks[i].free = 1;

            break;
        }
    }
}
