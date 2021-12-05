#ifndef ENVIORNEMENT_H
#define ENVIORNEMENT_H

#include "interprete/structs.h"
#include "interprete/hashmap.h"


#define MO (1024*1024)
#define MAX_SIZE_ID 512
#define STR_LENGTH 128
#define STACK_SIZE 256

struct value_s {

    unsigned int id;

    union {
        long long int val;
        char c;
        float f;
        char str[STR_LENGTH];
        char bool;
        struct func_s func;
    };
};

int init_environnement();
void display_stack();
void display_env();


int push_stack(struct value_s* val);
struct value_s* pop_stack();
struct value_s* get_stack(unsigned int offset);
struct value_s* dup_tos_stack();
struct value_s* seek_in_env(char * variable);
extern unsigned int tos;
extern unsigned int bos;
extern struct value_s** stack;
extern struct hmap_s *env_global;
extern struct hmap_s *env_local;

#endif