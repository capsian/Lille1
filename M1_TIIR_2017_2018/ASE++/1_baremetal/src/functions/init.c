#include "system/context.h"
#include "system/string.h"
#include "system/irq.h"
#include "drivers/screen.h"
#include "drivers/keyboard.h"
#include "functions/init.h"
#include "functions/mshell.h"
#include "skel/gdt.h"
#include "skel/idt.h"
#include "setup.h"

#define TICK 100000000

void init_shells(void* args) {

    puts("init_proc() enter ...\n");

    /* init n mshell */
    char ctx_name[6];
    strcpy(ctx_name, "tty");
    ctx_name[5] = '\0';

    for (int i = 1; i<4; i++) {

        if (i>9) {
            ctx_name[3] = '0' + (i / 10);
            ctx_name[4] = '0' + (i % 10);
        }
        else {
            ctx_name[3] = '0' + i;
            ctx_name[4] = '\0';
        }

        create_ctx(1000, shell_ctx, 0, ctx_name, i+1);
    }

    puts("init_proc() enter ...\n");
}

void init_star(void* args) {

    unsigned int lock = 0;

    while (1) {
        if (++lock == TICK) {
            lock = 0;
            puts(" * ");
        }
    }
}

void init_plus(void* args) {

    unsigned int lock = 0;

    while (1) {
        if (++lock == TICK) {
            lock = 0;
            puts(" + ");
        }
    }
}

void launch_init(unsigned int* mboot_info) {

    if (VERBOSE) {
        puts("init_star() with pid = "); put_number(RUNNING_PROCESS); puts(" \n");
        puts("init_plus() with pid = "); put_number(RUNNING_PROCESS + 1); puts(" \n");
        puts("shell_ctx() with pid = "); put_number(RUNNING_PROCESS + 2); puts(" \n");
    }

    create_ctx(1000, init_star, 0, "init_star", 1);
    create_ctx(1000, init_plus, 0, "init_plus", 2);
    create_ctx(1000, shell_ctx, 0, "shell", 1);
    //create_ctx(1000, init_shells, 0, "init_shells", 1);

    return;
}