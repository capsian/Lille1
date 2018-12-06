#include "hardware.h"
#include "core.h"
#include "lock.h"

void lock(){
  char lock;
    do {
      lock = _in(CORE_LOCK);
      
    } while(lock == 0);
}

void unlock(){
  _out(CORE_UNLOCK,1);
}
