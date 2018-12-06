#include "yield.h"

typedef struct sem_s {
  int count;
  ctx_s* lctx;
}sem_s;

void sem_init(sem_s*, int);
void sem_down(sem_s*);
void sem_up(sem_s*);
