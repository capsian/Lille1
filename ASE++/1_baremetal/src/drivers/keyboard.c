#include <memory.h>
#include <setup.h>
#include <system/context.h>
#include "skel/ioport.h"
#include "skel/idt.h"

#include "drivers/screen.h"
#include "drivers/keyboard.h"
#include "drivers/scancode.h"

#include "system/irq.h"
#include "system/signals.h"
#include "system/semaphore.h"

int m_capsL  = 0;
int m_vernum = 0;
int m_alt    = 0;
int m_altGr  = 0;
int m_ctr    = 0;

struct keyboard_s keyboard;
char *tab_ref = scancode_normal;

void keyboard_int(int_regs_t *r) {

    int display = 0;
    unsigned char c = _inb(KB_KEY);

    /* get the key */
    /* released key */
    if(c & 0x80) {

        /*puts(" released - ");
        put_number(c);
        puts(" - ");*/

        /* LSHIT */
        if (c == 170) {
            m_capsL = !m_capsL;
        }

        /* ALT */
        if (c==184) {
            m_alt = !m_alt;
        }

        /* ALTGR */
        if (c==224) {
            m_altGr = !m_altGr;
        }

        /* CTR */
        if (c==157) {
            m_ctr = !m_ctr;
        }
    }
    /* pressed key */
    else {

        /*puts(" pressed - ");
        put_number(c);
        puts(" - ");*/

        display = 1;

        /* LSHIT  || RSHIT  || CAPSLOCK */
        if ((c == 42) || (c == 54) || (c == 58)){
            m_capsL = !m_capsL;
        }

        /* VERNUM */
        if (c == 69) {
            m_vernum = !m_vernum;
        }

        /* BACKSPACE */
        if (c==14) {
            //putc(0x08);
            backCursor();
        }

        /* ALT */
        if (c==56) {
            m_alt = !m_alt;
        }

        /* ALTGR */
        if (c==224) {
            m_altGr = !m_altGr;
        }

        /* CTR */
        if (c==29) {
            m_ctr = !m_ctr;
        }

        /* F1 => F10 */
        if ( (c>=59) && (c <= 68) ) {
            //switch_screen(9 - (68 - c));
            return;
        }
    }

    /* update keyboard scancode */
    if (m_capsL)
        tab_ref = scancode_maj;
    else if (m_vernum)
        tab_ref =  scancode_vernum;
    else if (m_altGr)
        tab_ref =  scancode_altGR;
    else if (m_ctr)
        tab_ref = scancode_ctr;
    else
        tab_ref = scancode_normal;

    /*
     * catch sig_term
     * CTR+c
     *
     * */
    if (m_ctr && (c == 46)) {
        puts("CATCHED SIGTERM\n");
        catch_sig_term();
        return;
    }

    /* display */
    if (display) {
        if (tab_ref[c] != '\0') {
            if(keyboard.kb_take_sem.compteur <= 0) {
                putc(tab_ref[c]);
                keyboard.kb_buffer[keyboard.kb_buffer_pos++] = tab_ref[c];
                sem_up(&keyboard.kb_char_sem);
            }
        }
    }
}

void keyboard_setup() {

    /* init struct */
    sem_init(&keyboard.kb_take_sem, 1);
    sem_init(&keyboard.kb_char_sem, 0);
    keyboard.kb_mode = DIRECT_DISPLAY;
    keyboard.kb_buffer_pos = 0;
    memset(keyboard.kb_buffer, '\0', KB_BUFFER_SIZE);

    /* enable interrupt */
    idt_setup_handler(KB_IRQ, keyboard_int);
    irq_enable();
}

void read_line(char* buffer, unsigned int size) {

    char* tmp_c;
    int k = 0;

    /* clean buffer */
    memset(buffer, '\0', size);
    sem_down(&keyboard.kb_take_sem);


    /* block until \n */
    do {

        tmp_c = getc();

        for (int i=0; i<keyboard.kb_buffer_pos; i++) {
            /* backspace */
            if (tmp_c[0] == 0x08)
                k--;
            else
                buffer[k++] = tmp_c[i];
        }
    }
    while ( keyboard.kb_buffer[ keyboard.kb_buffer_pos - 1] != '\n');

    buffer[k - 1] = '\0';

    sem_up(&keyboard.kb_take_sem);
    return;
}

char* getc() {

    /* clean the structure */
    memset(keyboard.kb_buffer, '\0', KB_BUFFER_SIZE);
    keyboard.kb_buffer_pos = 0;

    sem_down(&keyboard.kb_char_sem);


    //while(keyboard.kb_buffer_pos == 0) { /*if (VERBOSE) puts("getc()\n");*/  };


    return keyboard.kb_buffer;
}