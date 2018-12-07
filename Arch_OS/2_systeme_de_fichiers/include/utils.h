#ifndef TP_UTILS_H
#define TP_UTILS_H

void empty_it();
void clean_buffer(unsigned char*);
void set_buffer(unsigned char*, char);
void display_buffer(unsigned char*);
void check_input(int, int);
void set_verbose(unsigned int v);

void mount(unsigned int vol);
void umount();

typedef enum { TRUE  = 1, FALSE = 0 } bool_t;

extern unsigned int verbose;

#endif
