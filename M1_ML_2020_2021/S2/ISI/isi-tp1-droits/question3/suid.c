#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    FILE *f;
    char c;

    printf("EUID: %d\n", geteuid());
    printf("EGID: %d\n", getegid());
    printf("RUID: %d\n", getuid());
    printf("RGID: %d\n\n", getgid());

    if ((f = fopen("/home/ubuntu/isi-tp1/mydir/data.txt", "r")) == NULL)
    {
        printf("Cannot open file \n");
        exit(0);
    }

    while ((c = fgetc(f)) != EOF)
        printf("%c", c);
    fclose(f);

    return 0;
}

