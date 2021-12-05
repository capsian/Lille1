#include "setup.h"

#include "drivers/keyboard.h"
#include "drivers/screen.h"

#include "functions/launcher.h"

#include "system/context.h"

/* multiboot entry-point with datastructure as arg. */
void main(unsigned int *mboot_info) {

    set_verbose(1);

    setup(mboot_info);
    keyboard_setup();

    puts("main() enter ...\n");

    launch_init();

    start_sched();

    puts("main() exit ...\n");

    return;
}
