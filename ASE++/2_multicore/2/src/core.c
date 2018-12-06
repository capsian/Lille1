#include <stdio.h>

#include "core.h"
#include "hardware.h"
#include "timer.h"
#include "irq.h"
#include "ctx.h"

struct core_s core_env[CORE_NCORE];

void boot() {


    asm("mov %%esp,%0" : "=r" (core_env[_in(CORE_ID)].esp) : :);
    asm("mov %%ebp,%0" : "=r" (core_env[_in(CORE_ID)].ebp) : :);

    printf("Core %d booting ..., esp:%p, ebp:%p\n", _in(CORE_ID), (core_env[_in(CORE_ID)].esp), (core_env[_in(CORE_ID)].ebp));

    current_ctxs[_in(CORE_ID)] = NULL;
    irq_enable();

    while(1);
}

void my_init_core() {

    IRQVECTOR[CORE_IRQ] = boot;

    for (unsigned short i = 0; i < CORE_NCORE; i++) {
        start_core(i);
        timer_redirect_on(i, TIMER_IRQ);
    }
}

void start_core(unsigned short ncore) {
    unsigned short tmp = _in(CORE_STATUS);
    unsigned short mycore = 1 << ncore;
    tmp |= mycore;
    _out(CORE_STATUS, tmp);
}

void stop_core(unsigned short ncore) {
    unsigned short tmp = _in(CORE_STATUS);
    unsigned short mycore = 1 << ncore;
    tmp &= (0xFFFF - mycore);
    _out(CORE_STATUS, tmp);
}
