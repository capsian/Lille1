#include <stdio.h>
#include <stdlib.h>

#include "hardware.h"
#include "init.h"
#include "timer.h"
#include "core.h"
#include "init_sched.h"
#include "ctx.h"


void empty_it() { }

void init_irq_vector() {
    for (int i = 0; i < 16; i++) {
        IRQVECTOR[i] = empty_it;
    }
}

void init() {

    if (init_hardware(INIFILENAMECORE) == 0) {
        fprintf(stderr, "Error in hardware initialization\n");
        exit(EXIT_FAILURE);
    }

    init_irq_vector();
    init_sched();
    my_init_core();
    init_timer();
    boot();
}
