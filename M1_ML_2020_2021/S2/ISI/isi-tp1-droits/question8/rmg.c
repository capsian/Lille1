#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "check_pass.h"

#define PWD_MAX_SIZE 16

int main(int argc, char const *argv[]) {
    struct stat sb;
    gid_t gid;
    uid_t uid;
    char password[PWD_MAX_SIZE], i = 0, c;

    gid = getgid();
    uid = getuid();
    stat(argv[1], &sb);

    if (gid != sb.st_gid) {
        printf("Wrong GID, Permission denied %s\n", argv[1]);
        return EXIT_FAILURE;
    }

    printf("Enter your password: ");
    scanf("%s", password);

    if (check_pass("/home/admin/passwd", uid, password) == 0) {
        int del = remove(argv[1]);
        if (!del)
            printf("%s removed !\n", argv[1]);
        else
            printf("error while removing %s\n", argv[1]);
    }
    else {
        printf("incorrect password !\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}