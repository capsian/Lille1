//
// Created by worker on 14/09/17.
//

#include <setjmp.h>
#include <stdio.h>

static jmp_buf buf;
static int i = 0;

static int cpt() {
    printf("enter cpt() .... i = %d\n",i);
    int j = 0;

    if (setjmp(buf)) {
        printf(" if ....  i = %d, j = %d\n",i,j);
        for (j=0; j<5; j++)
            i++;
    } else {
        printf(" else ....  i = %d, j = %d\n",i,j);
        for (j=0; j<5; j++)
            i--;
    }
    printf("exit cpt() i = %d | j = %d....\n",i,j);
}

int main() {
    printf("enter main() .... \n");
    int np = 0 ;

    cpt();

    if (! np++) {
        printf("longjmp !!\n");
        longjmp(buf,~0);
    }
    else
        printf("no longjmp !!\n");

    printf("exit main() i = %d\n", i );
}
