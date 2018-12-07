#include	"hardware.h"

typedef void (irq_handler_func_t) (void);

void setup_irq(unsigned int, irq_handler_func_t);
void start_hw();
void irq_disable();
void irq_enable();
void start_sched();
