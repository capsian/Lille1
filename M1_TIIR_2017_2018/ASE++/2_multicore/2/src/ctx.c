#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>

#include "ctx.h"
#include "core.h"
#include "hardware.h"
#include "irq.h"
#include "timer.h"
#include "lock.h"
#include "init_sched.h"

struct ctx_s *ring_ctx = NULL;
struct ctx_s *current_ctxs[CORE_NCORE];

struct ctx_s *create_ctx(int stack_size, func_t f, void *args, char *srl, char elected) {

    struct ctx_s *ctx = (struct ctx_s *) malloc(sizeof(struct ctx_s));

    assert(ctx != NULL);

    if (!init_ctx(ctx, stack_size, f, args, srl, elected)) {

        free(ctx);
        return NULL;
    } else {

        if (elected) {

            if (ring_ctx == NULL) {
                ring_ctx = ctx;
                ring_ctx->next = ctx;
            } else {
                ctx->next = ring_ctx->next;
                ring_ctx->next = ctx;
            }
        }
        else {

            lock();
            irq_disable();

            if (ring_ctx == NULL) {
                ring_ctx = ctx;
                ring_ctx->next = ctx;
            } else {
                ctx->next = ring_ctx->next;
                ring_ctx->next = ctx;
            }

            irq_enable();
            unlock();
        }
    }

    return ctx;
}

int init_ctx(struct ctx_s *ctx, int stack_size, func_t f, void *args, char *srl, char elected) {

    ctx->stack = malloc(sizeof(char) * stack_size);

    ctx->magic = MAGIC;
    ctx->elected = elected;
    ctx->entrypoint = f;
    ctx->args = args;
    ctx->state = CTX_READY;
    ctx->esp = ctx->stack + stack_size - sizeof(void *);
    ctx->ebp = ctx->esp;
    strncpy(ctx->serial, srl, 32);

    return ctx->stack != NULL;
}

/* simple round robin election */
struct ctx_s * elect_ctx() {

    struct ctx_s * tmp_start, *tmp_end;

    tmp_start = ring_ctx;
    tmp_end = ring_ctx;

    do {
        if(tmp_start->elected == 0) {
            tmp_start->elected = 1;
            return tmp_start;
        }

        tmp_start = tmp_start->next;
    }
    while (tmp_start != tmp_end);

    return NULL;
}

void yield() {

    irq_disable();
    printf("yield on core  %d\n", _in(CORE_ID));

    /* CORE-0: have to reset timer only !! (and print some info) */
    if (_in(CORE_ID) == 0) {

        reset_timer();
        for(long int tick_tempo = 1 << 15;tick_tempo > 0; tick_tempo--);
        show_ring_ctx();
        irq_enable();

    } else {

        lock();

        struct ctx_s * tmp = elect_ctx();

        if (tmp == NULL){

            if (current_ctxs[_in(CORE_ID)] == NULL) {
                printf("KILL\n");
                printf("NO process to switch on core %d, ebp:%p, esp:%p\n",_in(CORE_ID), core_env[_in(CORE_ID)].ebp, core_env[_in(CORE_ID)].esp );

                unlock();

                asm("mov %0, %%ebp" : :"r" (core_env[_in(CORE_ID)].ebp) :);
                asm("mov %0, %%esp" : :"r" (core_env[_in(CORE_ID)].esp) :);

                /* CREATING NEW CTX to yield on */
                //irq_enable();
                //while(1);
                tmp = create_ctx(1<<16,procs_plus,0,"yield_plus",1);
            }
        }

        if (tmp != NULL)
            switch_to_ctx(tmp);
        else {
            unlock();
            irq_enable();
        }
    }
}

void switch_to_ctx(struct ctx_s *ctx) {

    assert(ctx->magic = MAGIC);

    /* get current exec core */
    struct ctx_s *tmp_curr = current_ctxs[_in(CORE_ID)];

    /* store current ctx */
    if (tmp_curr != NULL) {
        tmp_curr->elected = 0;
        asm("mov %%esp,%0" : "=r" (tmp_curr->esp) : :);
        asm("mov %%ebp,%0" : "=r" (tmp_curr->ebp) : :);
    }

    current_ctxs[_in(CORE_ID)] = ctx;

    asm("mov %0, %%ebp" : :"r" (current_ctxs[_in(CORE_ID)]->ebp) :);
    asm("mov %0, %%esp" : :"r" (current_ctxs[_in(CORE_ID)]->esp) :);

    irq_enable();
    unlock();

    if (current_ctxs[_in(CORE_ID)]->state == CTX_READY) {
        start_ring_ctx(current_ctxs[_in(CORE_ID)]);
    }
}

void start_ring_ctx(struct ctx_s* ctx) {

    printf("start_ring_ctx on core:%d !!!!! ctx:%s\n", _in(CORE_ID), ctx->serial);

    assert(ctx != NULL);
    assert(ctx->state == CTX_READY);

    ctx->state = CTX_RUNNING;
    ctx->entrypoint((int) ctx->args);
    ctx->state = CTX_TERMINATED;

    printf("start_ring_ctx on core:%d -- remove!!!!! ctx:%s \n", _in(CORE_ID), ctx->serial);

    remove_ring_ctx();
}

void remove_ring_ctx() {

    lock();
    irq_disable();

    struct ctx_s *ctx = current_ctxs[_in(CORE_ID)];

    assert(ctx != NULL);
    assert(ctx->state == CTX_TERMINATED);

    if (ctx != ctx->next) {

        struct ctx_s *last_ctx = ctx;

        while (last_ctx->next != ctx) {
            last_ctx = last_ctx->next;
        }

        last_ctx->next = ctx->next;
        ring_ctx = last_ctx;
        free(ctx);
        current_ctxs[_in(CORE_ID)] = NULL;

        //show_ring_ctx();

        unlock();
        irq_enable();

        yield();

    } else {

        printf("REMOVE: no ctx !!\n");
        free(ctx);
        irq_enable();
        unlock();

        exit(0);
    }
}

void show_ring_ctx() {

    //irq_disable();

    struct ctx_s *tmp = ring_ctx;
    printf("show_ring_ctx() on the core %d\n", _in(CORE_ID));
    do {
        printf("proc:%s (%p), state:%d, elected:%d, ebp:%p, esp:%p\n", tmp->serial, (void*) tmp, tmp->state, tmp->elected, tmp->ebp, tmp->esp);
        tmp = tmp->next;

    } while (tmp != ring_ctx);

    //irq_enable();
}

void show_current_ctxs() {

    //irq_disable();

    for (int i=0; i<CORE_NCORE; i++) {
        printf("%d) %p - ", i, (void*) current_ctxs[i]);
    }

    printf("\n");

    //irq_enable();

}
