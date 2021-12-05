//
// Created by worker on 14/09/17.
//

#include <setjmp.h>
#include <stdio.h>

static jmp_buf buf;

static int mul(int d) {
    printf("[mul] enter ...\n");
    int i;
    printf(" &i = %p | saisie : \n",&i);

    switch (scanf("%d", &i)) {
        case EOF :
            printf(" case : scanf() = EFO, return 1\n");
            return 1; /* neutral element */
        case 0 :
            printf(" case : scanf() = 0, return mul(d+1)\n");
            return mul(d+1); /* erroneous read */
        case 1 :
            printf(" case : 1 ");
            if (i) {
                printf(" case : scanf() = 1, i = %d, return %d * mul(d+1)\n",i,i);
                return i * mul(d+1);
            }
            else {
                printf(" case : scanf() = 1, i = %d, longjmp(), never display printf()\n",i);
                longjmp(buf,~0);
                printf(" IM DEAD ?\n");
                return 0;
            }
    }
    printf("[mul] exit ...\n");
}

int main() {
    printf("[main] enter ...\n");

    int product = -1;

    if (setjmp(buf)) {

        printf(" if setjmp ...\n");
        product = 0;
    } else {

        printf(" else setjmp ...\n");
        product = mul(0);
    }

    printf(" product = %d\n", product);
    printf("[main] exit ...\n");
}