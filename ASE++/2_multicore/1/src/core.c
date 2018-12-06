#include "core.h"
#include "hardware.h"
#include "timer.h"
#include "irq.h"
#include <stdio.h>

void boot(){
  printf("Core %d booting ...\n",_in(CORE_ID));
  irq_enable();
  doIt();
}

void doIt(){
  char lock;
  while(1){
    do {
      lock = _in(CORE_LOCK);
    } while(lock == 0);
    printf("[%d",_in(CORE_ID));
    for (size_t i = 0; i < (1 << 20); i++) {
    }
    printf("-%d]",_in(CORE_ID));
    _out(CORE_UNLOCK,1);
    for (size_t j = 0; j < (1 << 25); j++);
  }
}
void my_init_core(){
  IRQVECTOR[CORE_IRQ] = boot;
  for (unsigned short i = 0; i < CORE_NCORE; i++) {
    start_core(i);
    if(i % 2 == 1){
      timer_redirect_on(i,TIMER_IRQ);
    }
  }
}

void start_core(unsigned short ncore){
  unsigned short tmp = _in(CORE_STATUS);
  unsigned short mycore = 1 << ncore;
  tmp |= mycore;
  _out(CORE_STATUS,tmp);
}

void stop_core(unsigned short ncore){
  unsigned short tmp = _in(CORE_STATUS);
  unsigned short mycore = 1 << ncore;
  tmp &= (0xFFFF - mycore);
  _out(CORE_STATUS,tmp);
}
