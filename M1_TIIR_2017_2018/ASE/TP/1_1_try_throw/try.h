#ifndef TP1_TRY_H
#define TP1_TRY_H

#endif //TP1_TRY_H

typedef int (func_t)(int);

struct ctx_s {

    void* rsp;
    void* rbp;
};
typedef struct ctx_s ctx_s;

int _try(ctx_s*, func_t*, int);
int _throw(ctx_s*, int);
