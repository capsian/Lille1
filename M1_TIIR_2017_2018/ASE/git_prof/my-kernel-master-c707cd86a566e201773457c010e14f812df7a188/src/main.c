#include "ioport.h"
#include "gdt.h"
#include "idt.h"

void clear_screen();				/* clear screen */
void putc(char aChar);				/* print a single char on screen */
void puts(char *aString);			/* print a string on the screen */
void puthex(int aNumber);			/* print an Hex number on screen */

void timer_int(int_regs_t *r)
{
    puts(".");
}

/* multiboot entry-point with datastructure as arg. */
void main(unsigned int * mboot_info)
{
	/* clear the screen */
	clear_screen();
    puts("Early boot.\n"); 
    puts("\t-> Setting up the GDT... ");
    gdt_init_default();
    puts("OK\n");

    puts("\t-> Setting up the IDT... ");
    setup_idt();
    puts("OK\n");
	
    puts("\n\n");
    
    idt_setup_handler(0, timer_int);
    __asm volatile("sti");

    /* print something */
	puts("Hello World!\n\n");
	puts("Multiboot Info at ");
	puthex((unsigned int)mboot_info);
	puts("\n");

	for(;;) ;
}

/* base address for the video output assume to be set as character oriented by the multiboot */
unsigned char *video_memory = (unsigned char *) 0xB8000;

/* clear screen */
void clear_screen() {
  int i;
  for(i=0;i<80*25;i++) { 			/* for each one of the 80 char by 25 lines */
    video_memory[i*2+1]=0x0F;			/* color is set to black background and white char */
    video_memory[i*2]=(unsigned char)' '; 	/* character shown is the space char */
  }
}

/* print a string on the screen */
void puts(char *aString) {
  char *current_char=aString;
  while(*current_char!=0) {
    putc(*current_char++);
  }
}

/* print an number in hexa */
char *hex_digit="0123456789ABCDEF";
void puthex(int aNumber) {
  if(aNumber==0) putc('0');
  else {
    unsigned int tmp=*((unsigned int *)&aNumber);
    while(tmp!=0) {
      putc(hex_digit[tmp&0xF]);
      tmp=(tmp>>4);
    }
  }
}

/* print a char on the screen */
int cursor_x=0;					/* here is the cursor position on X [0..79] */
int cursor_y=0;					/* here is the cursor position on Y [0..24] */

void setCursor() {
  int cursor_offset = cursor_x+cursor_y*80;
  _outb(0x3d4,14);
  _outb(0x3d5,((cursor_offset>>8)&0xFF));
  _outb(0x3d4,15);
  _outb(0x3d5,(cursor_offset&0xFF));
}

void putc(char c) {
  if(cursor_x>79) {
    cursor_x=0;
    cursor_y++;
  }
  if(cursor_y>24) {
    cursor_y=0;
    clear_screen();
  }
  switch(c) {					/* deal with a special char */
    case '\r': cursor_x=0; break;		/* carriage return */
    case '\n': cursor_x=0; cursor_y++; break; 	/* new ligne */	
    case 0x8 : if(cursor_x>0) cursor_x--; break;/* backspace */
    case 0x9 : cursor_x=(cursor_x+8)&~7; break;	/* tabulation */
						/* or print a simple character */
    default  : 
      video_memory[(cursor_x+80*cursor_y)*2]=c;
      cursor_x++;
      break;
  }
  setCursor();
}


