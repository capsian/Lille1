#include <stdio.h>
#include "try.h"

static struct ctx_s ctx;

int mul(int d) {

    int i;

    switch (scanf("%d", &i)) {
        case EOF :
            return 1; /* neutral element  */
        case 0 :
            return mul(d+1); /* erroneous read */
        case 1 :
            if (i)
                return i * mul(d+1);
            else
                return _throw(&ctx,i);
    }
}

int main() {

    int product;

    printf("A list of int, please\n");
    product = _try(&ctx,mul,0);
    printf("product = %d\n", product);
}
