#ifndef SCREEN_H
#define SCREEN_H

void clear_screen();                /* clear screen */
void putc(char aChar);              /* print a single char on screen */
void puts(char *aString);           /* print a string on the screen */
void puthex(int aNumber);           /* print an Hex number on screen */
void put_number(int number);
void backCursor();


void setCursor();

#endif
