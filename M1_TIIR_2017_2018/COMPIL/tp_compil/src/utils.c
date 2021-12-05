#include <stdio.h>
#include <stdlib.h>

#include "utils.h"

unsigned int VERBOSE = 0;

void set_verbose(int enable) {

    if (enable)
        VERBOSE = 1;
    else
        VERBOSE = 0;
}

/*
 * lvl:
 *      0 - ERROR
 *      1 - WARNING
 *      2 - INFO
 * mode:
 *      1 - EXIT
 *      0 - NO EXIT
 */
void mlog(char* msg, unsigned int lvl, unsigned int ext) {

    if (VERBOSE) {
        switch (lvl) {
            /* ERROR */
            case 0:
                printf("[ERROR] %s\n",msg);
                break;
                /* WARNING */
            case 1:
                printf("[WARNING] %s\n",msg);
                break;
                /* INFO */
            case 2:
                printf("[INFO] %s\n",msg);
                break;
            default:
                printf("log - SHOULD NEVER HAPPEN !!\n");
                exit(EXIT_FAILURE);
        }

        fflush(stdin);

        if (ext)
            exit(EXIT_FAILURE);
    }
}

int my_str_len(char *str1) {

    int i = 0;

    while (str1[i] != '\0')
        i++;

    return i;
}

int my_compare(char *str1, char *str2) {

    // fail
    if (my_str_len(str1) != my_str_len(str2))
        return -1;
    else {

        for (int i = 0; i < my_str_len(str1); i++) {
            if (str1[i] != str2[i])
                return -1;
        }

        // all right, equ
        return 0;
    }
}