#ifndef ENVIORNEMENT_H
#define ENVIORNEMENT_H

#include "interpreter/structs.h"

#define MAX_SIZE_ID 512
#define STR_LENGTH 128

struct value_s {

    unsigned int id;
    union {
        int val;
        char c;
        float f;
        char str[STR_LENGTH];
        char bool;
        struct func_s func;
    };
};

struct environnement_s{
  char id[MAX_SIZE_ID];
  struct value_s * value;
  struct environnement_s * next;
  struct environnement_s * prev;
};

struct value_s * get(char * id,struct environnement_s * env);
struct environnement_s * put(char * id,struct value_s * value,struct environnement_s * env);

#endif