#include <setup.h>
#include "drivers/keyboard.h"
#include "drivers/screen.h"
#include "system/context.h"
#include "system/string.h"
#include "system/exit.h"

#include "functions/launcher.h"

void shell_ctx(void *args) {

    char cmd[32];

    // always running
    do {

        puts("mshell>");
        read_line(cmd, 32);

        if (!strcmp(cmd,"clr")) {
            clear_screen();
            continue;
        }

        if (!strcmp(cmd,"ping_pong")) {
            launch_ping_pong();
            continue;
        }

        if (!strcmp(cmd,"ps")) {
            launch_ps();
            continue;
        }

        if (!strcmp(cmd,"mshell")) {

            create_ctx(1000, shell_ctx, 0, "mshell_from_shell", 0);

            continue;
        }

    } while (strcmp(cmd,"exit"));

    puts("exit ....\n");
    exit();
}