//
// Created by worker on 14/09/17.
//

#include "ex4.h"
#include <setjmp.h>
#include <stdio.h>
#include <stdlib.h>


int _try(ctx_s* pctx, func_t* f, int arg) {
    printf("_try enter ...\n");

    asm("movl %%esp, %0;" : "=r"(pctx->esp));
    asm("movl %%ebp, %0;" : "=r"(pctx->ebp));

    printf(" pctx->esp = %p || pctx->ebp = %p \n",pctx->esp,pctx->ebp);
    printf("_try exit ...\n");
    return f(arg);
}

int _throw(ctx_s* pctx, int r) {
    printf("_throw enter with r = %d ...\n",r);
    printf(" pctx->esp = %p || pctx->ebp = %p \n",pctx->esp,pctx->ebp);

    asm("movl %0, %%esp;" : :"r"(pctx->esp));
    asm("movl %0, %%ebp;" : :"r"(pctx->ebp));

    printf("_throw exit with r = %d ... (not eq)\n",r);
    return r;
}

int callback(int d) {
    return d * d;
}


int main(void) {

    int t;
    ctx_s* orgiCntxt = malloc(sizeof(ctx_s));

    t = _try(orgiCntxt, callback, 5);
    printf("t = %d\n", t);

    return 0;
}
