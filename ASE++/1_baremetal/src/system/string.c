#include "system/string.h"


void *memset(void *s, int c, unsigned int n) {

    unsigned char* p = s;

    while(n--)
        *p++ = (unsigned char)c;

    return s;
}

void *memcpy(void *dest, const void *src, unsigned int n) {

    char *dp = dest;
    const char *sp = src;

    while (n--)
        *dp++ = *sp++;

    return dest;
}

int memcmp(const void* s1, const void* s2, unsigned int n) {

    const unsigned char *p1 = s1, *p2 = s2;

    while(n--)
        if( *p1 != *p2 )
            return *p1 - *p2;
        else
            p1++,p2++;

    return 0;
}

int strcmp(const char* s1, const char* s2) {

    while(*s1 && (*s1==*s2))
        s1++,s2++;

    return *(const unsigned char*)s1 - *(const unsigned char*)s2;
}

char *strcpy(char *dest, const char* src) {

    char *ret = dest;

    while ((*dest++ = *src++) != 0);

    return ret;
}
