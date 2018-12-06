#include "drivers/screen.h"
#include "skel/ioport.h"
#include "system/context.h"
#include "system/string.h"
#include "system/irq.h"
#include "system/malloc.h"

unsigned char *video_memory = (unsigned char *) 0xB8000;
unsigned int cursor_x = 0;
unsigned int cursor_y = 0;


/* clear screen */
void clear_screen() {

    irq_disable();

    for (int i = 0; i < 80 * 25; i++) {            /* for each one of the 80 char by 25 lines */
        video_memory[i * 2 + 1] = 0x0F;            /* color is set to black background and white char */
        video_memory[i * 2] = (unsigned char) ' ';    /* character shown is the space char */
    }

    cursor_x = 0;
    cursor_y = 0;

    irq_enable();
}

void putc(char c) {

    irq_disable();

    if (cursor_x > 79) {
        cursor_x = 0;
        cursor_y++;
    }

    if (cursor_y > 24) {
        cursor_y = 0;
        clear_screen();
    }

    /* deal with a special char */
    switch (c) {
        /* carriage return */
        case '\r': {
            cursor_x = 0;
            break;
        }
            /* new ligne */
        case '\n': {
            cursor_x = 0;
            cursor_y++;
            break;
        }
            /* backspace */
        case 0x8 : {
            if (cursor_x > 0) cursor_x--;
            break;
        }
            /* tabulation */
        case 0x9 : {
            cursor_x = (cursor_x + 8) & ~7;
            break;
        }
            /* or print a simple character */
        default  : {
            video_memory[(cursor_x + 80 * cursor_y) * 2] = c;
            cursor_x++;
            break;
        }
    }

    irq_enable();

    setCursor();
}

/* print a string on the screen */
void puts(char *aString) {

    irq_disable();

    char *current_char = aString;

    while (*current_char != 0) {
        putc(*current_char++);
    }

    irq_enable();
}

/* print an number in hexa */
char *hex_digit = "0123456789ABCDEF";

void puthex(int aNumber) {

    irq_disable();

    unsigned int tmp;

    if (aNumber == 0)
        putc('0');

    else {

        tmp = *((unsigned int *) &aNumber);

        puthex(tmp >> 4);
        putc(hex_digit[tmp & 0xF]);
    }

    irq_enable();
}

void put_number(int number) {

    char c = '0';

    if (number != 0) {
        put_number(number / 10);
        putc(c + (number % 10));
    } else
        putc(c);
}

void setCursor() {

    irq_disable();

    int cursor_offset = cursor_x + cursor_y * 80;
    
    _outb(0x3d4, 14);
    _outb(0x3d5, ((cursor_offset >> 8) & 0xFF));
    _outb(0x3d4, 15);
    _outb(0x3d5, (cursor_offset & 0xFF));

    irq_enable();
}

void backCursor() {

    irq_disable();


    if ((cursor_x > 0) && (cursor_x < 80)) {

        cursor_x--;
        setCursor();

        video_memory[(cursor_x + 80 * cursor_y) * 2] = '\0';

        return;
    }

    if ((cursor_x == 0) && (cursor_y > 0)) {
        cursor_y--;
        cursor_x = 79;
        setCursor();
        return;
    }

    irq_enable();
}