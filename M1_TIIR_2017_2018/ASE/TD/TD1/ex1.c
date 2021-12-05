//
// Created by worker on 14/09/17.
//

#include <setjmp.h>
#include <stdio.h>
static int i = 0;
static jmp_buf buf;

int main() {

    int j;

    printf("enter .... i = %d \n",i);

    if (setjmp(buf)){
        printf("if ....  i = %d \n",i);
        for (j=0; j<5; j++)
            i++;
    }
    else {
        printf("else .... i = %d \n",i);
        for (j=0; j<5; j++)
            i--;
        longjmp(buf,~0);
        printf("IM DEAD ?? %d \n",i);
    }

    printf("exit i = %d\n",i);

    return 0;
}