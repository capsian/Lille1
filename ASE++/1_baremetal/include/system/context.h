#ifndef CTX_H
#define CTX_H

#include "drivers/screen.h"
#include "semaphore.h"

#define MAGIC 0xCAFEBABE
#define TIMER_IRQ	0

typedef void (func_t) (void *);

extern unsigned int RUNNING_PROCESS;
extern struct ctx_s * current_ctx;

enum state_e {CTX_READY, CTX_RUNNING, CTX_TERMINATED, CTX_FREEZED};

struct ctx_s {

    int magic;
    char id[32];
    unsigned int pid;

    func_t * entrypoint;
    void * args;
    enum state_e state;

    void * esp;
    void * ebp;
    char * stack;

    unsigned int screen_id;
    struct ctx_s * next;
};

void start_sched();

int init_ctx(struct ctx_s * ctx,int stack_size,func_t f,void * args, char* id, unsigned int screen_id);
struct ctx_s * create_ctx(int stack_size, func_t f,void* args, char* id, unsigned int screen_id);

void switch_to_ctx(struct ctx_s *);
void start_current_ctx();
void remove_current_ctx();
void yield();

#endif
