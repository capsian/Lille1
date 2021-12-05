#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define MAGIC 0xCAFEBABE
typedef void (func_t) (void*);

enum state_e {
	ctx_RDY,
	ctx_RUN,
	ctx_TERM
};

struct ctx_s {

	void* rbp;
	void* rsp;
	int magic;
	void* args;
	enum state_e state;
	func_t* entrypoint;
	char* stack;
};

void f_ping(void* arg);
void f_pong(void* arg);
int init_ctx(struct ctx_s*, int, func_t, void*);
void switch_to_ctx(struct ctx_s*);
void start_current_ctx();

struct ctx_s ctx_ping;
struct ctx_s ctx_pong;

struct ctx_s* current_ctx = NULL;

int main(int argc, char* argv[]) {

	init_ctx(&ctx_ping, 16384, f_ping, NULL);
	init_ctx(&ctx_pong, 16384, f_pong, NULL);
	switch_to_ctx(&ctx_ping);
	exit(EXIT_SUCCESS);
}

void f_ping(void* args) {

	while(1) {
		printf("A") ;
		switch_to_ctx(&ctx_pong);
		printf("B") ;
		switch_to_ctx(&ctx_pong);
		printf("C") ;
		switch_to_ctx(&ctx_pong);
	}
}

void f_pong(void* args) {

	while(1) {
		printf("1") ;
		switch_to_ctx(&ctx_ping);
		printf("2") ;
		switch_to_ctx(&ctx_ping);
	}
}

int init_ctx(struct ctx_s* ctx, int stack_size, func_t f, void* args) {
	
	ctx->stack = malloc(sizeof(char) * stack_size);
	ctx->args = args;
	ctx->magic = MAGIC;
	ctx->state = ctx_RDY;
	ctx->entrypoint = f;
	ctx->rsp = ctx->stack + stack_size - sizeof(void*);
	ctx->rbp = ctx->rsp;
	
	return (ctx->stack != NULL); 
}

void switch_to_ctx(struct ctx_s* ctx) {
	
	assert(ctx->magic == MAGIC);
	
	if (current_ctx != NULL) {
		asm("mov %%rsp, %0;" : "=r"(current_ctx->rsp)::);
    	asm("mov %%rbp, %0;" : "=r"(current_ctx->rbp)::);
	}
	
	current_ctx = ctx;
	
	asm("mov %0, %%rsp;" : :"r"(current_ctx->rsp):);
    asm("mov %0, %%rbp;" : :"r"(current_ctx->rbp):);
    
    if (current_ctx->state == ctx_RDY) {
    	start_current_ctx();
    }
    
    return;
}

void start_current_ctx() {

		current_ctx->state = ctx_RUN;
    	current_ctx->entrypoint(current_ctx->args);
    	current_ctx->state = ctx_TERM;
    	exit(0); 
}

