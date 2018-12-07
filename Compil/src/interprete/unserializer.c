#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "interprete/environnement.h"
#include <interprete/defines.h>
#include "interprete/unserializer.h"
#include "interprete/evaluate.h"
#include "token.h"
#include "utils.h"

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
            sprintf(tmp_log,"exp1:%p, exp2:%p, valExp1:%s, valExp2:%s\n", (void*) exp1, (void*) exp2, exp1->lit.token->value, exp2->lit.token->value);
            mlog(tmp_log, 2 ,0);

            return init_binaryop(tok, exp1, exp2);
        case 4: /* CALL */
            exp1 = read_expression(-1);
            exps = read_expression_list();
            return init_call(exp1, exps);
        case 5: /* FUNCTION */
            mlog("NAMED FUNC !!", 2 ,0);
            tok = read_token();
            toks = read_token_list();
            stmts = read_statement_list();

            return init_funct(tok, toks, stmts);
        case 6: /* FUNCTION */
            mlog("ANONYM FUNC !!", 2 ,0);
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
        case 22: /* BRANCH */
            tok = read_token();
            return init_branch(tok);
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

int main(int argc, char** argv) {

    set_verbose(1);

    /* check input */
    if (argc != 2)
        mlog("unserializer <input.parsed>", 0, 1);

    infile = fopen(argv[1],"r");

    struct list_node_s* stmt_list = read_statement_list();
    struct list_node_s* tmp = stmt_list;

    while(tmp != NULL) {

        sprintf(tmp_log, "stmt id = %d", tmp->value->id);
        mlog(tmp_log, 2, 0);

        tmp = tmp->next;
    }

    /* global env */
    if (!init_environnement())
        mlog("ERROR while init_env", 0, 1);

    mlog("== evaluate ==", 2, 0);
    evaluate_env(stmt_list);

    mlog("== display FINAL stack ==", 2, 0);
    display_stack();

    mlog("free stmt_list ...", 2, 0);
    free(stmt_list);
    mlog("Done !!", 2, 0);


    mlog("free env ...", 2, 0);
    table_destroy(env_global);
    mlog("Done !!", 2, 0);

    mlog("free stack ...", 2, 0);
    free(stack);
    mlog("Done !!", 2, 0);

    mlog("bye :)", 2, 0);
    return 0;
}
