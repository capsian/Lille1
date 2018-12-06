#include "../include/semaphore.h"
#include "../include/tmr.h"
#include <stdlib.h>
#include <stdio.h>

void sem_init( sem_s* sem, int val) {
  sem->count = val;
  sem->lctx = NULL;
}

void sem_down(sem_s* sem) {
  irq_disable();

  sem->count--;

  if (sem->count < 0) {

      struct ctx_s* tmp = current_ctx->next;

      while (tmp->next != current_ctx) {
        tmp = tmp->next;
      }

      if (tmp == current_ctx) {
        printf("%s\n", "EXIT_FAILURE");
        exit(-1);
      } else {
          tmp->next = current_ctx->next;
          current_ctx->next = sem->lctx;
          sem->lctx = current_ctx;
          switch_to_ctx(tmp->next);
      }
  }
  irq_enable();
}

void sem_up(sem_s* sem) {
  irq_disable();

  sem->count++;

  if (sem->count <= 1) {

    if (sem->lctx != NULL) {

      struct ctx_s* ctx = sem->lctx;
      sem->lctx = ctx->next;
      ctx->next = current_ctx->next;
      current_ctx->next = ctx;
    }
  }

  irq_enable();
}
