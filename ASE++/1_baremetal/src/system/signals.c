#include "system/signals.h"
#include "system/context.h"
#include "system/irq.h"
#include "system/malloc.h"

void catch_sig_term() {
    remove_current_ctx();
    RUNNING_PROCESS--;
}

void catch_sig_stop() {

}

void kill(unsigned int pid) {

    irq_disable();

    struct ctx_s * ctx = current_ctx;

    while(ctx->next != ctx) {

        if (ctx->pid == pid) {

        }
    }

    irq_enable();
}