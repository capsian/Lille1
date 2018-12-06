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
	struct ctx_s* next;
};

struct ctx_s* create_ctx(int stack_size, func_t f, void* args);
void doit(void *arg);
int init_ctx(struct ctx_s* ctx, int stack_size, func_t f, void* args);
void yield();
void switch_to_ctx(struct ctx_s* ctx);
void start_current_ctx();
