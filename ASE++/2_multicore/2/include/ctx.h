#ifndef CTX_H
#define CTX_H

#include "core.h"

#define MAGIC 0xCAFEBABE

#define TIMER_CLOCK	0xF0
#define TIMER_PARAM     0xF4
#define TIMER_ALARM     0xF8
#define TIMER_IRQ	2
typedef void (func_t) (int);

enum state_e { CTX_READY, CTX_SUSPEND, CTX_RUNNING, CTX_TERMINATED};

struct ctx_s {
  char serial[32];
  void * esp;
  void * ebp;
  func_t * entrypoint;
  int magic;
  enum state_e state;
  char * stack;
  void * args;
  struct ctx_s * next;
  char elected;
};

struct ctx_s * create_ctx(int, func_t,void*, char* serial,char elected);
int init_ctx(struct ctx_s * ,int,func_t,void *, char* serial,char elected);

void yield();
void switch_to_ctx(struct ctx_s *);
struct ctx_s * elect_ctx();

void show_ring_ctx();
void show_current_ctxs();

void start_ring_ctx(struct ctx_s* ctx);
void remove_ring_ctx();

extern struct ctx_s* ring_ctx;
extern struct ctx_s* current_ctxs[CORE_NCORE];

#endif
