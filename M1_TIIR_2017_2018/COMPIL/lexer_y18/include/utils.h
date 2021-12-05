#ifndef UTILS_H
#define UTILS_H

#define TMP_LOG_SIZE 256

extern unsigned int VERBOSE;
extern char* tmp_log;

void mlog(char* msg, int lvl, int ext);

void set_verbose(int enable);
int my_str_len(char *str1);
int my_compare(char *str1, char *str2);

#endif
