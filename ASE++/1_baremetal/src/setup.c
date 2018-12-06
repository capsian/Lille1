#include "skel/gdt.h"
#include "skel/idt.h"
#include "drivers/screen.h"

unsigned int VERBOSE = 0;

void setup(unsigned int *mboot_info) {

    /* clear the screen */
    clear_screen();
    puts("Early boot.\n");
    puts("\t-> Setting up the GDT... ");
    gdt_init_default();
    puts("OK\n");

    puts("\t-> Setting up the IDT... ");
    setup_idt();
    puts("OK\n");

    /* print something */
    puts("Hello World!\n\n");
    puts("Multiboot Info at ");
    puthex((unsigned int) mboot_info);
    puts("\n");
}

void set_verbose(char enable) {

    if (enable)
        VERBOSE = 1;
    else
        VERBOSE = 0;
}