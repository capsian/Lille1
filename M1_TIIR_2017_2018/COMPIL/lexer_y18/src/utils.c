#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

unsigned int VERBOSE = 0;
char* tmp_log;

void set_verbose(int enable) {

    tmp_log = malloc(TMP_LOG_SIZE);

    if (enable)
        VERBOSE = 1;
    else
        VERBOSE = 0;
}

void mlog(char* msg, int lvl, int ext) {

    if (ext)
        VERBOSE = 1;

    if (VERBOSE)
        switch (lvl) {
            case 0:
                printf("[ERROR] %s", msg);
                if (ext)
                    exit(EXIT_FAILURE);
            case 1:
                printf("[WARNING] %s\n",msg);
                if (ext)
                    exit(EXIT_FAILURE);
            case 2:
                printf("[INFO] %s\n",msg);
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