#include <setup.h>
#include "system/context.h"
#include "system/malloc.h"
#include "system/irq.h"
#include "system/string.h"
#include "drivers/screen.h"

#include "skel/idt.h"

unsigned int RUNNING_PROCESS = 0;
struct ctx_s * current_ctx = NULL;

void start_sched() {

    if (VERBOSE) {
        puts("start_sched() !!  \n");
    }

    idt_setup_handler(TIMER_IRQ, yield);
}

int init_ctx(struct ctx_s * ctx,int stack_size,func_t f,void * args, char* id, unsigned int screen_id) {

    ctx->stack = malloc(sizeof(char)*stack_size);

    if(ctx->stack == NULL)
        return 0;

    if (VERBOSE) {
        //puts("malloc ctx->stack = "); puthex((int) ctx->stack); puts(", sizeof(char)*stack_size = ");put_number(sizeof(char)*stack_size); puts(" \n");
    }

    memset(ctx->id, '\0', 32);
    strcpy(ctx->id, id);
    ctx->magic = MAGIC;
    ctx->pid = RUNNING_PROCESS++;

    ctx->entrypoint = f;
    ctx->args = args;
    ctx->state = CTX_READY;
    ctx->esp = ctx->stack + stack_size - sizeof(void *);
    ctx->ebp = ctx->esp;

    ctx->screen_id = screen_id;

    return (ctx->stack != NULL);
}

struct ctx_s * create_ctx(int stack_size, func_t f,void* args, char* id, unsigned int screen_id) {

    if (VERBOSE) {
        //puts("create_ctx() ... enter  \n");
    }

    struct ctx_s * ctx = malloc(sizeof(struct ctx_s));

    if (ctx == NULL) {

        if (VERBOSE) {
            puts("create_ctx() ... malloc FAILS !!! \n");
        }

        return NULL;
    }

    if (VERBOSE) {
        //puts("malloc ctx = "); puthex((int) ctx); puts("\n");
    }

    /* fail */
    if(!init_ctx(ctx, stack_size, f, args, id, screen_id)) {

        if (VERBOSE) {
            puts("create_ctx() ... init_ctx() FAILS ");
        }

        free(ctx);

        if (VERBOSE) {
            puts(" !!! \n");
        }

        return NULL;
    }
    else {

        irq_disable();

        /* cycle */
        if(current_ctx == NULL) {
            current_ctx = ctx;
            current_ctx->next = ctx;
        }else {
            ctx->next = current_ctx->next;
            current_ctx->next = ctx;
        }

        irq_enable();
    }

    if (VERBOSE) {
        //puts("create_ctx() ... exit with ctx->pid = "); put_number(ctx->pid); puts("\n");
    }

    return ctx;
}

void yield() {

    irq_disable();
    switch_to_ctx(current_ctx->next);
}

void switch_to_ctx(struct ctx_s * ctx) {

    if(ctx->magic != MAGIC){
        return;
    }

    /* store current ctx */
    if(current_ctx != NULL) {

        asm("mov %%esp,%0" : "=r" (current_ctx->esp) : :);
        asm("mov %%ebp,%0" : "=r" (current_ctx->ebp) : :);
    }

    current_ctx = ctx;
    asm("mov %0,%%ebp" : :"r" (current_ctx->ebp):);
    asm("mov %0,%%esp" : :"r" (current_ctx->esp):);

    irq_enable();

    if(current_ctx->state == CTX_READY) {
        start_current_ctx();
    }
    else if (current_ctx->state == CTX_TERMINATED) {
        remove_current_ctx();
    }
    else if (current_ctx->state == CTX_FREEZED) {
        yield();
    }

    return;
}

void start_current_ctx() {

    struct ctx_s * ctx = current_ctx;

    ctx->state = CTX_RUNNING;
    ctx->entrypoint(ctx->args);
    ctx->state = CTX_TERMINATED;

    return;
}

void remove_current_ctx() {

    irq_disable();

    struct ctx_s * ctx = current_ctx;

    if(ctx != ctx->next) {

        struct ctx_s* last_ctx = ctx;

        while(last_ctx->next != ctx) {
            last_ctx = last_ctx->next;
        }

        last_ctx->next = ctx->next;
        free(ctx);

        irq_enable();

        yield();

    } else {

        free(ctx);
        irq_enable();
        puts("\nKILLING LAST CTX !!!\n");

        return;
    }
}