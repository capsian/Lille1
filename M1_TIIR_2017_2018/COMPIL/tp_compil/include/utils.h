#ifndef UTILS_H
#define UTILS_H

extern unsigned int VERBOSE;

void set_verbose(int enable);
void mlog(char* msg, unsigned int lvl, unsigned int ext);


int my_str_len(char *str1);
int my_compare(char *str1, char *str2);

#endif
