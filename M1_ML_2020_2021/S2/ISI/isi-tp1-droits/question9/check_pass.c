#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "check_pass.h"

int check_pass(char *filename, uid_t user_id, char *password)
{
    FILE *f;
    char *line = NULL, delim[] = ":", *pwd, *uid;
    size_t len = 0;
    int res = -1;

    if ((f = fopen(filename, "r")) != NULL) {
        while (getline(&line, &len, f) != -1) {
            uid = strtok(line, delim);
            pwd = strtok(NULL, delim);
            if (atoi(uid) == user_id) {
                res = strcmp(pwd, crypt(password, "isi"));
                break;
            }
        }
        fclose(f);
    }
    else {
        printf("error with file %s", filename);
    }

    if (line)
        free(line);

    return res;
}
