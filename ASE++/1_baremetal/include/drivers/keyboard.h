#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "system/semaphore.h"

#define KB_IRQ	1
#define KB_KEY 0x60
#define KB_BUFFER_SIZE 4

enum kb_m {NONE, DIRECT_DISPLAY, BUFFER_DISPLAY};

struct keyboard_s {
    char kb_buffer[KB_BUFFER_SIZE];
    unsigned int kb_buffer_pos;
    enum kb_m kb_mode;

    struct sem_s kb_take_sem;
    struct sem_s kb_char_sem;
};

extern struct keyboard_s keyboard;

void keyboard_setup();
void read_line(char* buffer, unsigned int size);
char* getc();

#endif