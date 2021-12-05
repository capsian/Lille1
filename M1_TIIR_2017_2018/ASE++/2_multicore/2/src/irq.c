#include "irq.h"
#include "hardware.h"

void irq_enable(){
  _mask(1);
}

void irq_disable(){
  _mask(15);
}
