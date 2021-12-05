#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pwd.h>
#include "check_pass.h"

#define PWD_MAX_SIZE 16

int main(int argc, char const *argv[]) {
    FILE *passwd_file, *tmp_passwd_file;
    char *passwd_line = NULL, delim[] = ":", *pwd, *uid;
    size_t len = 0, size = -1;
    char new_pwd[PWD_MAX_SIZE], old_pwd[PWD_MAX_SIZE], *crypt_pwd;
    int found = 0;

    uid_t user_id = getuid();

    // read passwd file
    passwd_file = fopen("/home/admin/passwd2", "r");
    if (passwd_file != NULL) {
        while (size = getline(&passwd_line, &len, passwd_file) != -1) {
            uid = strtok(passwd_line, delim);
            pwd = strtok(NULL, delim);
            if (atoi(uid) == user_id)
                found = 1;
                break;
        }
        fclose(passwd_file);
    }

    // The user has already a password
    if (found > 0) {
        printf("Enter old password: ");
        scanf("%s", old_pwd);
        printf("\n=>old password: %s\n", old_pwd);

        if (strcmp(pwd, crypt(old_pwd, "isi"))) {
            printf("Not matching !\n");
            free(passwd_line);
            return EXIT_FAILURE;
        }
    }

    printf("Enter new password: ");
    scanf("%s", new_pwd);
    printf("\n=> new password: %s\n", new_pwd);

    // Write the new password
    passwd_file = fopen("/home/admin/passwd2", "r");
    tmp_passwd_file = fopen("/home/admin/passwd2.tmp", "a");
    if (passwd_file != NULL && tmp_passwd_file != NULL) {
        while (getline(&passwd_line, &len, passwd_file) != -1) {
            uid = strtok(passwd_line, delim);
            pwd = strtok(NULL, delim);

            if (atoi(uid) != user_id)
                fprintf(tmp_passwd_file, "%s:%s:\n", uid, pwd);
        }
        fprintf(tmp_passwd_file, "%d:%s:\n", user_id, crypt(new_pwd, "isi"));
        free(passwd_line);
        fclose(passwd_file);
        fclose(tmp_passwd_file);
    }

    printf("\n");
    remove("/home/admin/passwd2");
    rename("/home/admin/passwd2.tmp", "/home/admin/passwd2");

    return EXIT_SUCCESS;
}