#include "timer.h"
#include "hardware.h"
#include "irq.h"
#include "core.h"
#include <stdio.h>

static int irqn = 0;
void timer_tick(){

  printf("Hello from IT %d on core %d \n",irqn++,_in(CORE_ID));
  reset_timer();
}

void init_timer(){
  IRQVECTOR[TIMER_IRQ] = timer_tick;
  start_timer();
}


void start_timer(){
  _out(TIMER_PARAM,128+64);
  _out(TIMER_ALARM,0xFFFFFFFF - 500 );
}

void reset_timer(){
  _out(TIMER_ALARM,0xFFFFFFFF - 500 );
}

void timer_redirect_on(unsigned short ncore, unsigned int interupt){
  unsigned short tmp = _in(CORE_IRQMAPPER+ncore);
  interupt = 1 << interupt;
  tmp |= interupt;
  _out(CORE_IRQMAPPER+ncore,tmp);
}

void timer_redirect_off(unsigned short ncore, unsigned int interupt){
  unsigned short tmp = _in(CORE_IRQMAPPER+ncore);
  interupt = 1 << interupt;
  tmp &= (0xFFFF - interupt);
  _out(CORE_IRQMAPPER+ncore,tmp);
}
