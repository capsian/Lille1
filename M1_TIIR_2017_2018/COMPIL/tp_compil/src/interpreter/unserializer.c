#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "interpreter/global_environnement.h"
#include "interpreter/defines.h"
#include "interpreter/unserializer.h"
#include "interpreter/evaluate.h"
#include "token.h"

FILE *infile;

unsigned char read_byte() {
    unsigned char c;
    if(!feof(infile)) c=fgetc(infile); else {fprintf(stderr,"unexpected eof !\n"); exit(1);}

    return c;
}

int read_word16() {
    int h,l;
    h=read_byte()&255;
    l=read_byte()&255;

    return (h<<8)|l;
}

int read_word32() {
    int h=read_word16()&65535;
    int l=read_word16()&65535;

    return (h<<16)|l;
}

void print_token_s(struct token_s* tok) {

    printf("token: id = %d, line = %d, column = %d, length = %d\n", tok->id, tok->line, tok->column, tok->length);
    printf("value = %s\n", tok->value);
}

struct token_s* read_token() {

    struct token_s* tok = malloc(sizeof(struct token_s));
    assert(tok != NULL);

    tok->id     = read_byte();
    tok->line   = read_word16();
    tok->column = read_word16();
    tok->length = read_word16();
    tok->value  = malloc(sizeof(unsigned char) * tok->length);
    assert(tok->value != NULL);

    for (int i =0; i< tok->length; i++) {
        tok->value[i] = read_byte();
    }

    return tok;
}

struct list_token_s* add_token_to_list(struct list_token_s* tok_list, struct token_s* tok) {

    struct list_token_s* tmp = tok_list;
    struct list_token_s* new = malloc(sizeof(struct list_token_s));

    assert(new != NULL);
    new->next = NULL;
    new->tok = tok;

    if (tok_list == NULL) {
        tok_list = new;
    }
    else {
        while(tmp->next != NULL) {
            tmp = tmp->next;
        }

        tmp->next = new;
    }

    return tok_list;
}

struct list_token_s* read_token_list() {

    unsigned int len = read_word32();
    struct token_s* tok;
    struct list_token_s* tok_list = malloc(sizeof(struct list_token_s));

    assert(tok_list != NULL);

    tok_list->next = NULL;

    while (len-- > 0) {
        tok = read_token();
        tok_list = add_token_to_list(tok_list, tok);
    }

    return tok_list;
}

struct node_s* read_expression(int nodeId) {

    
    if (nodeId == -1)
        nodeId = read_byte();
    
    struct token_s* tok;
    struct list_token_s* toks;
    struct node_s* exp1;
    struct node_s* exp2;
    struct node_s* exp3;
    struct list_node_s* exps;
    struct list_node_s* stmts;

    switch (nodeId) {

        case 0: /* LIT */
            tok = read_token();
            return init_litteral(tok);
        case 1: /* PrefixOP */
            tok = read_token();
            exp1 = read_expression(-1);
            return init_prefixop(tok, exp1);
        case 2: /* POSTFIX */
            tok = read_token();
            exp1 = read_expression(-1);
            return init_postfixop(tok, exp1);
        case 3: /* BINARYOP */
            tok = read_token();
            exp1 = read_expression(-1);
            exp2 = read_expression(-1);
            return init_binaryop(tok, exp1, exp2);
        case 4: /* CALL */
            exp1 = read_expression(-1);
            exps = read_expression_list();
            return init_call(exp1, exps);
        case 5: /* FUNCTION */
            tok = read_token();
            toks = read_token_list();
            stmts = read_statement_list();
            return init_funct(tok, toks, stmts);
        case 6: /* FUNCTION */
            toks = read_token_list();
            stmts = read_statement_list();
            return init_funct(NULL, toks, stmts);
        case 7: /* TERNARY */
            exp1 = read_expression(-1);
            exp2 = read_expression(-1);
            exp3 = read_expression(-1);
            return init_ternary(exp1, exp2, exp3);
        default:
            printf("read_expression() default !!! SHOULD NEVER HAPPEN !! nodeId = %d\n", nodeId);
            exit(EXIT_FAILURE);
    }
}

struct list_node_s* add_node_to_list(struct list_node_s* list, struct node_s* insert) {

    struct list_node_s* new = malloc(sizeof(struct list_node_s));

    new->value = insert;
    new->next  = NULL;

    if (list == NULL) {
        list = new;
    }
    else {

        struct list_node_s* tmp = list;

        while (tmp->next != NULL)
            tmp = tmp->next;

        tmp->next = new;
    }

    return list;
}

struct list_node_s* read_expression_list() {

    struct node_s* tmp;
    struct list_node_s* exp_list = NULL;

    unsigned int len = read_word32();

    while (len-- > 0) {
        tmp = read_expression(-1);
        assert(tmp != NULL);
        exp_list = add_node_to_list(exp_list, tmp);
    }

    return exp_list;
}

struct node_s* read_statement() {

    struct token_s* tok;
    struct node_s* exp;
    struct list_node_s* body1, *body2;

    int nodeId = read_byte();

    switch(nodeId) {
        case 16:    /* VAR2 */
            tok = read_token();
            return init_var1(tok);
        case 17:    /* VAR1 */
            tok = read_token();
            exp = read_expression(-1);
            return init_var2(tok, exp);
        case 18: /* RETURN */
            return init_return1();
        case 19:    /* RETURN */
            exp = read_expression(-1);
            return init_return2(exp);
        case 20:    /* IfThenElse */
            exp = read_expression(-1);
            body1 = read_statement_list();
            body2 = read_statement_list();
            return init_ifthenelse(exp, body1, body2);
        case 21:    /* WHILE */
            exp = read_expression(-1);
            body1 = read_statement_list();
            return init_while(exp, body1);
        default:    /* Expre */
            printf("read_statement, default, nodeId:%d\n",nodeId);
            exp = read_expression(nodeId);
            return exp;
    }
}


struct list_node_s* read_statement_list() {

    struct node_s* tmp;
    struct list_node_s* stmt_list = NULL;

    unsigned int len = read_word32();

    while (len-- > 0) {
        tmp = read_statement();
        assert(tmp != NULL);
        stmt_list = add_node_to_list(stmt_list, tmp);
    }

    return stmt_list;
}

void usage() {

    printf("unserializer <input.parsed>\n");
    exit(EXIT_FAILURE);
}

int main(int argc, char** argv) {

    /* check input */
    if (argc != 2)
        usage();

    infile = fopen(argv[1],"r");

    struct list_node_s* stmt_list = read_statement_list();
    struct list_node_s* tmp = stmt_list;

    while(tmp != NULL) {
        printf("stmt id = %d\n", tmp->value->id);
        tmp = tmp->next;
    }

    evaluate_env(stmt_list);

    free(stmt_list);

    return 0;
}