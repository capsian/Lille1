#ifndef CORE_H

#define CORE_H
#define CORE_ENABLE 1
#define CORE_NCORE 6
#define CORE_STATUS 0x80
#define CORE_IRQMAPPER 0x82
#define CORE_ID 0x126
#define CORE_LOCK 0x98
#define CORE_UNLOCK 0x99
#define CORE_IRQ 0

void my_init_core();
void start_core(unsigned short ncore);
void doIt();
#endif
