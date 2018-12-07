#include "functions/ps.h"
#include "system/context.h"
#include "system/irq.h"
#include "system/malloc.h"
#include "drivers/screen.h"
#include "drivers/keyboard.h"
#include "setup.h"

static int nb_ctx = 0;
struct ctx_s * tmp_ctx;

void ps() {

    while (1) {
        if (nb_ctx != RUNNING_PROCESS) {

            irq_disable();

            nb_ctx = RUNNING_PROCESS;

            tmp_ctx = current_ctx;

            /* ACTIF */
            puts("\nActive Process : \n");
            while (tmp_ctx->next != current_ctx) {

                puts(" process: "); puts(tmp_ctx->id); puts(", pid: "); put_number(tmp_ctx->pid); puts(" \n");
                tmp_ctx = tmp_ctx->next;
            }

            /* KEYBOARD SEM */
            puts("Keyboard Blocked Process : \n");
            tmp_ctx = keyboard.kb_take_sem.bloquer;
            while (tmp_ctx != NULL) {

                puts(" process: "); puts(tmp_ctx->id); puts(", pid: "); put_number(tmp_ctx->pid); puts(" \n");
                tmp_ctx = tmp_ctx->next;
            }

            /* KEYBOARD KEY SEM */
            puts("Keyboard Waiting char Process : \n");
            tmp_ctx = keyboard.kb_char_sem.bloquer;
            while (tmp_ctx != NULL) {

                puts(" process: "); puts(tmp_ctx->id); puts(", pid: "); put_number(tmp_ctx->pid); puts(" \n");
                tmp_ctx = tmp_ctx->next;
            }

            irq_enable();
        }
    }
}

void launch_ps() {

    if (VERBOSE) {
        puts("lauch_mshell() with pid = "); put_number(RUNNING_PROCESS); puts(" \n");
    }

    create_ctx(16384, ps, 0, "ps", 9);
}