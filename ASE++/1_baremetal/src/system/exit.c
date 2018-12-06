#include "system/exit.h"
#include "system/context.h"


void exit() {

    int tmp = 0;

    asm("movl %0,%%eax" ::"r"(tmp):);
    asm("movl %0,%%ebx" ::"r"(tmp):);
    //asm("int 0x80");

    RUNNING_PROCESS--;
}