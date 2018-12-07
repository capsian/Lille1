/* ------------------------------
   $Id: tmr.c 69 2007-05-11 11:54:15Z phm $
   ------------------------------------------------------------

   Program a timer

   Philippe Marquet, march 2007

   A minimal example of a program using the timer interface.

*/

#include <stdlib.h>
#include <stdio.h>
#include "../include/hardware.h"
#include "../include/hwconfig.h"
#include "../include/tmr.h"

static void empty_it(void) {
    return;
}

void setup_irq(unsigned int irq, irq_handler_func_t handler) {

  /* dummy interrupt handlers */
  for (unsigned int i=0; i<16; i++) {
    if (i != irq) {
      IRQVECTOR[i] = empty_it;
    } else {
      IRQVECTOR[i] = handler;
    }
  }
}

void start_hw() {

  /* init hardware */
  if (init_hardware(INIFILENAME) == 0) {
     fprintf(stderr, "Error in hardware initialization\n");
      exit(EXIT_FAILURE);
  }

}

void irq_enable() {
  _mask(1);
}

void irq_disable() {
  _mask(15);
}

void start_sched(irq_handler_func_t handler) {

  start_hw();
  setup_irq(2,handler);

  _out(TIMER_PARAM,128+64); /* reset + alarm on + 8 tick / alarm */
  _out(TIMER_ALARM,0xFFFFFFFF - 20);  /* alarm at next tick (at 0xFFFFFFFF) */

  irq_enable();
  handler();

}
