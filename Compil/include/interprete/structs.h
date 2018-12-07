#ifndef STRUCTS_H
#define STRUCTS_H

#include "token.h"
#include "interprete/unserializer.h"


struct node_s;

/* LIT */
struct literal_s {
    struct token_s * token;
};

/* PREFIX */
struct prefixop_s {
    struct token_s * token;
    struct node_s * exp;
};

/* POSTFIX */
struct postfixop_s {
    struct token_s * token;
    struct node_s * exp;
};

/* BINARYOP */
struct binaryop_s {
    struct token_s * token;
    struct node_s * exp1;
    struct node_s * exp2;
};

/* CALL */
struct call_s {
    struct node_s * func;
    struct list_node_s* args;
};

/* FUNCTION
 * FUNC | NAMED FUNC | ANONYMOUS FUNC
  */
struct func_s {
    struct token_s* token;
    struct list_token_s* args;
    struct list_node_s* body;    /* STATEMENTS */
};

/* TERNARY */
struct ternary_s {
    struct node_s* condition;
    struct node_s* thn;
    struct node_s* els;
};

/* VAR */
struct var2_s {
    struct token_s* token;
    struct node_s* exp;
};

struct var1_s {
    struct token_s* token;
};

/* RETURN */
struct return_s {
    struct node_s* exp;
};

/* IFTHENELSE */
struct ifthenelse_s {
    struct node_s *   exp;
    struct list_node_s* thn;
    struct list_node_s* els;
};

/* WHILE */
struct while_s {
    struct node_s* condition;
    struct list_node_s *  body;
};

/* BRANCH */
struct branch_s {
    struct token_s *tok;
};

/* NODE */
struct node_s {
    unsigned int id;
    union {
        struct literal_s lit;
        struct prefixop_s prefixop;
        struct postfixop_s postfixop;
        struct binaryop_s binaryop;
        struct call_s call;
        struct func_s func;
        struct ternary_s ternary;
        struct var1_s var1;
        struct var2_s var2;
        struct return_s ret;
        struct ifthenelse_s ifthenelse;
        struct while_s whil;
        struct branch_s branch;
    };
};

/* For give a list of node like in while */
struct list_node_s{
    struct node_s * value;
    struct list_node_s * next;
};


struct node_s* init_litteral(struct token_s * token);
struct node_s* init_prefixop(struct token_s * token,struct node_s * exp);
struct node_s* init_postfixop(struct token_s * token,struct node_s * exp);
struct node_s* init_binaryop(struct token_s * token,struct node_s * exp1,struct node_s * exp2);
struct node_s* init_call(struct node_s * func,struct list_node_s* args);
struct node_s* init_funct(struct token_s * token,struct list_token_s * args,struct list_node_s * body);
struct node_s* init_ternary(struct node_s * condition,struct node_s * thn,struct node_s * els);
struct node_s* init_var2(struct token_s * token,struct node_s * exp);
struct node_s* init_var1(struct token_s * token);
struct node_s* init_return1();
struct node_s* init_return2(struct node_s * exp);
struct node_s* init_ifthenelse(struct node_s * exp,struct list_node_s * thn,struct list_node_s * els);
struct node_s* init_while(struct node_s * condition,struct list_node_s * body);
struct node_s* init_branch(struct token_s* tok);

#endif
