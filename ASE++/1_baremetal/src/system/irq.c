#include "skel/ioport.h"
#include "system/irq.h"

void irq_enable() {
    __asm volatile("sti");
    _outb(0x20,0x20);
}

void irq_disable() {
    __asm volatile("cli");
}