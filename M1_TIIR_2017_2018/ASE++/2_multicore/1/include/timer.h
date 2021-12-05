#ifndef TIMER_H
#define  TIMER_H

#define TIMER_CLOCK 0xF0
#define TIMER_PARAM 0xF4
#define TIMER_ALARM 0xF8
#define TIMER_IRQ 2

void init_timer();
void start_timer();
void reset_timer();
void timer_redirect_on(unsigned short ncore,unsigned int interupt);
void timer_redirect_off(unsigned short ncore,unsigned int interupt);
#endif
