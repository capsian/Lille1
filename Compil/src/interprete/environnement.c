#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "interprete/environnement.h"
#include "utils.h"

unsigned int bos = 0;
unsigned int tos = 0;

struct value_s** stack;

struct hmap_s *env_global;
struct hmap_s *env_local;

int init_environnement() {

    stack = malloc(sizeof(struct value_s*) * STACK_SIZE);
    table_create(STACK_SIZE);

    return ( (stack != NULL) && (env_global != NULL));
}

int push_stack(struct value_s* val) {

    stack[tos++] = val;
    return tos - 1;
}

struct value_s* pop_stack() {

    struct value_s* ret = stack[tos-1];

    stack[tos-1] = NULL;
    tos--;

    return ret;
}

struct value_s* dup_tos_stack() {

    struct value_s* res = malloc(sizeof(struct value_s));

    memcpy(res, stack[tos], sizeof(struct value_s));

    return res;
}

void display_stack() {

    if (!VERBOSE)
        return;

    printf(" === display_stack ===\n");
    printf("bos: %d, tos:%d\n", bos, tos);
    for (unsigned int i = bos; i<tos; i++) {

        printf("stack[%d] = %p, ", i, (void*) stack[i]);

        if (stack[i] == NULL) {
            printf("\n");
            continue;
        }

        if (stack[i])
            printf("tokId:%d", stack[i]->id);
        if (stack[i]->id == 130)
            printf(", val = %lld", stack[i]->val);

        printf("\n");
    }
    printf("============\n");
}

void display_env() {

    if (!VERBOSE)
        return;

    struct hmap_s* iter = env_local;
    int i = 0;

    printf(" === display_env [tos=%d]===\n",tos);
    while (iter != NULL) {

        printf("env:%d, (%p) , bos_local=%d\n", i++, (void*) iter, iter->bos_local);
        iter = iter->next;
    }
    printf("============\n");

}

struct value_s *seek_in_env(char * variable) {

    /*sprintf(tmp_log,"seek_in_env enter with %s", variable);
    mlog(tmp_log,2,0);*/

    long int offset = table_get(variable);

    /*sprintf(tmp_log,"seek_in_env: offset %ld", offset);
    mlog(tmp_log,2,0);*/

    return stack[offset];
}

