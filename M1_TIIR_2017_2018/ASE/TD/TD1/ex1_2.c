//
// Created by worker on 14/09/17.
//

#include <setjmp.h>
#include <stdio.h>
static int i = 0;
static jmp_buf buf;

int main() {

    int j = 0;

    printf("enter .... i = %d \n",i);

    if (setjmp(buf)) {
        printf("if ....  i = %d, j = %d\n",i,j);
        for (; j<5; j++) {
            printf(" %d \n",j);
            i++;
        }
    }
    else {
        printf("else .... i = %d, j = %d\n",i,j);
        for (; j<5; j++) {
            printf(" %d \n",j);
            i--;
        }

        longjmp(buf,~0);
        printf("IM DEAD ?? %d \n",i);
    }

    printf("exit i = %d\n",i);

    return 0;
}