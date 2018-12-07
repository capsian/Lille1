#ifndef STRING_H
#define STRING_H

void *memset(void *s, int c, unsigned int n);
void *memcpy(void *dest, const void *src, unsigned int n);
int memcmp(const void * s1, const void * s2, unsigned int n);

int strcmp(const char * s1, const char * s2);
char *strcpy(char *dest, const char *src);

#endif
