#include "hardware.h"
#include "init.h"
#include "timer.h"
#include "core.h"
#include "irq.h"
#include <stdio.h>
#include <stdlib.h>

void empty_it(){

}

void init_irq_vector(){
  for (int i = 0; i < 16; i++) {
    IRQVECTOR[i] = empty_it;
  }
}

void init(){
  if (init_hardware(INIFILENAMECORE) == 0) {
	   fprintf(stderr, "Error in hardware initialization\n");
     exit(EXIT_FAILURE);
  }
  init_irq_vector();
  my_init_core();
  init_timer();
  irq_enable();
  printf("Core %d booting ...\n",_in(CORE_ID));
  doIt();
}
