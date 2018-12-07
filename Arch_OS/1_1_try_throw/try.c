#include <stdio.h>
#include <stdlib.h>
#include "try.h"

static int anchor;

int _try(ctx_s* pctx, func_t* f, int arg) {
    
    asm("mov %%rsp, %0;" : "=r"(pctx->rsp));
    asm("mov %%rbp, %0;" : "=r"(pctx->rbp));

    return f(arg);
}

int _throw(ctx_s* pctx, int r) {

    anchor = r;

    asm("mov %%rsp, %0;" : :"r"(pctx->rsp));
    asm("mov %%rbp, %0;" : :"r"(pctx->rbp));

    return anchor;
}

// todo completeme
int init_ctx(ctx_s* ctx, int stack_size, func_t f, void* args) {
	
	ctx->rbp = malloc(stack_size);
	
	asm("mov %%rbp, %0;" : :"r"(ctx->rbp));
	
	return f( (int) args);
	return 0;
}
