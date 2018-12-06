/* ------------------------------
   $Id: c.ins,v 1.1 2003-02-21 14:33:51 marquet Exp $
   ------------------------------------------------------------

   memory isolation
   Philippe Marquet, Nov 2017
   
*/

#include "../../include/2/mi_syscall.h"
#include "../../include/2/mmu_handler_1.h"
#include "../../include/utils.h"
#include "../../include/hardware.h"
#include "../../include/1/mmu.h"

int current_process;

static void switch_to_process0(void) {

    current_process = 0;
    _out(MMU_CMD, MMU_RESET);
}

static void switch_to_process1(void) {

    current_process = 1;
    _out(MMU_CMD, MMU_RESET);
}

int main() {

    /* init hardware + IRQVECTOR */
    setup();

    IRQVECTOR[SYSCALL_SWTCH_0] = switch_to_process0;
    IRQVECTOR[SYSCALL_SWTCH_1] = switch_to_process1;
    IRQVECTOR[MMU_IRQ] = mmu_handler_1;

    _mask(0x1001);

    init();

    return 0;
}
