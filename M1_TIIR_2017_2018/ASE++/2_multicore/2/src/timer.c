#include "timer.h"
#include "hardware.h"
#include "core.h"
#include "ctx.h"

void init_timer(){
  IRQVECTOR[TIMER_IRQ] = yield;
  start_timer();
}

void start_timer(){
  _out(TIMER_PARAM,128+64);
  _out(TIMER_ALARM,0xFFFFFFFF - 200 );
}

void reset_timer(){
  _out(TIMER_ALARM,0xFFFFFFFF - 200 );
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
