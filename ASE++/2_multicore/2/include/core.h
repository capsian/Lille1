#ifndef CORE_H

#define CORE_H
#define CORE_ENABLE 1
#define CORE_NCORE 6
#define CORE_STATUS 0x80
#define CORE_IRQMAPPER 0x82
#define CORE_ID 0x126
#define CORE_IRQ 0

struct core_s {
    void* ebp;
    void* esp;
};

extern struct core_s core_env[CORE_NCORE];

void my_init_core();
void start_core(unsigned short ncore);
void stop_core(unsigned short ncore);

void boot();

#endif
