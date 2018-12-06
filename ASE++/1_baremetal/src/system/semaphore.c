#include "setup.h"

#include "system/context.h"
#include "system/semaphore.h"
#include "system/malloc.h"
#include "system/irq.h"

#include "drivers/screen.h"

#include "functions/launcher.h"

void sem_init(struct sem_s * sem, unsigned int val) {
  sem->compteur = val;
  sem->bloquer = NULL;
}

void sem_down(struct sem_s * sem) {

  irq_enable();

  if (VERBOSE) {
    //puts("\nsem_down(), current_ctx.pid = "); put_number(current_ctx->pid); puts(" \n");
  }

  sem->compteur--;

  if(sem->compteur < 0){

    struct ctx_s * tmp = current_ctx->next;

    while(tmp->next != current_ctx){
      tmp = tmp->next;
    }

    if(tmp == current_ctx){


      puts("\n ================== \n KERNEL PANICCCCC \n ================== \n");
      //launch_init();

    }else {

      tmp->next = current_ctx->next;
      current_ctx->next = sem->bloquer;
      sem->bloquer = current_ctx;

      switch_to_ctx(tmp->next);
    }
  }

  irq_enable();
}
void sem_up(struct sem_s * sem) {

  irq_disable();

  sem->compteur++;

  if(sem->compteur <= 1){

    if(sem->bloquer != NULL){

      struct ctx_s * ctx = sem->bloquer;

      sem->bloquer = ctx->next;
      ctx->next = current_ctx->next;
      current_ctx->next = ctx;
    }
  }

  if (VERBOSE) {
    //puts("\nsem_up(), current_ctx.pid = "); put_number(current_ctx->pid);
    //puts(", i will release current_ctx.next.pid = "); put_number(current_ctx->next->pid); puts("\n");
  }

  irq_enable();
}
