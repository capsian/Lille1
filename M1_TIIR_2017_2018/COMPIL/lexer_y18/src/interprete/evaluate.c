#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include "symbol.h"
#include "interprete/environnement.h"
#include "interprete/structs.h"
#include "interprete/evaluate.h"
#include "interprete/unserializer.h"
#include "utils.h"


int evaluate_env(struct list_node_s *list_node) {

    struct list_node_s *tmp = list_node;
    int res;

    while (tmp != NULL) {

        mlog("evaluate_env display:",2,0);
        display_env();
        display_stack();

        res = evaluate_statement(tmp->value);

        switch (res) {
            case INTRP_RETURN:
                //mlog("evaluate_env RET",2,0);
                return res;
            case INTRP_OK:
                break; /* CONTIUNE EVALUATION */
            case INTRP_CONTINUE:
                return res;
            case INTRP_BREAK:
                return res;
            default:
                //mlog("evaluate_env SHOULD NEVER HAPPEN",0,0);
                return INTRP_ERR;
        }

        tmp = tmp->next;
    }

    return INTRP_OK;
}

void print_value(struct value_s *res) {

    if (res == NULL) {
        printf("print_value: NULL \n");
        return;
    }

    switch (res->id) {
        case BOOLEAN:
            if(res->bool)
                printf("print_value: bool = true\n");
            else
                printf("print_value: bool = false\n");
            break;
        case INTEGER:
            printf("print_value: int = %lld\n", res->val);
            break;
        case FLOAT:
            printf("print_value: float = %f\n", res->f);
            break;
        case STRING:
            printf("print_value: string = %s\n", res->str);
            break;
        case CHAR:
            printf("print_value: char = %c\n", res->c);
            break;
        default:
            printf("print_value fail !! unkown id:%d\n", res->id);
    }
}

int evaluate_statement(struct node_s *node) {

    switch (node->id) {

        case 16:    /* VAR1 */
            return eval_var1(node->var1);
        case 17:    /* VAR2 */
            return eval_var2(node->var2);
        case 18: /* RETURN */
            return eval_return1(node->ret);
        case 19:    /* RETURN */
            return eval_return2(node->ret); /* TODO CHECK !! */
        case 20:    /* IfThenElse */
            return eval_ifthenelse(node->ifthenelse);
        case 21:    /* WHILE */
            return eval_while(node->whil);
        case 22: /* BRANCH */
            return eval_branch(node->branch);
        default:
            mlog("default: evaluate_statement, delegate to evaluate_expression... ", 2, 0);
            int res = evaluate_expression(node);
            /* DISPLAY */
            pop_stack();
            //print_value(pop_stack());
            return res;
    }
}

int evaluate_expression(struct node_s *node) {

    switch (node->id) {

        case 0: /* LIT */
            return eval_litteral(node->lit);
        case 1: /* PrefixOP */
            return eval_prefixop(node->prefixop);
        case 2: /* POSTFIX */
            return eval_postfixop(node->postfixop);
        case 3: /* BINARYOP */
            return eval_binaryop(node->binaryop);
        case 4: /* CALL */
            return eval_call(node->call);
        case 5: /* FUNCTION */
            return eval_funct(node->func);
        case 6: /* FUNCTION */
            return eval_funct(node->func);
        case 8: /* TERNARY */
            return eval_ternary(node->ternary);
        default:
            sprintf(tmp_log, "evaluate_expression , SHOULD NEVER HAPPEN !!, tokId:%d", node->id);
            mlog(tmp_log, 0, 1);
            return INTRP_ERR; /* make gcc happy :) */
    }
}


int eval_litteral(struct literal_s lit) {

    mlog("eval_litteral() ... enter", 2, 0);

    struct value_s *res = malloc(sizeof(struct value_s));
    struct value_s *found=NULL;

    switch (lit.token->id) {
        /* JUST PUSH IT ON STACK */
        case INTEGER:
            res->id = lit.token->id;
            res->val = atoi(lit.token->value);
            push_stack(res);
            break;
        /* FIND IT IN ENV && PUSH REF */
        case IDENTIFIER:
            found = seek_in_env(lit.token->value);
            assert(found != NULL);
            memcpy(res, found, sizeof(struct value_s));
            push_stack(res);
            break;
        /* JUST PUSH IT ON STACK */
        case STRING:
            res->id = lit.token->id;
            strcpy(res->str, lit.token->value);
            push_stack(res);
            break;
        default:
            sprintf(tmp_log, "evaluate eval_litteral ,NOT IMPLEMENTED , tokId:%d", res->id);
            free(res);
            mlog(tmp_log, 0, 1);
    }

    return INTRP_OK;
}

void process_inc(struct value_s* value) {

    switch (value->id) {
        case INTEGER:
            value->val++;
            break;
        case FLOAT:
            value->f++;
            break;
        case CHAR:
            value->c++;
            break;
        default:
            sprintf(tmp_log, "process_inc, valueID:%d", value->id);
            mlog(tmp_log, 0, 1);
            break;
    }
}

void process_dec(struct value_s* value) {

    switch (value->id) {
        case INTEGER:
            value->val--;
            break;
        case FLOAT:
            value->f--;
            break;
        case CHAR:
            value->c--;
            break;
        default:
            sprintf(tmp_log, "process_dec, valueID:%d", value->id);
            mlog(tmp_log, 0, 1);
            break;
    }
}

int eval_prefixop(struct prefixop_s prefixop) {

    mlog("eval_prefixop() ... enter ", 2, 0);

    if (prefixop.exp->id != IDENTIFIER) {
        mlog("eval_prefixop NOT IDENTIFIER",0,1);
    }

    struct value_s *res = seek_in_env(prefixop.exp->lit.token->value);

    /* PROCESS */
    switch (prefixop.token->id) {

        case INCREMENT:
            process_inc(res);
            break;

        case DECREMENT:
            process_dec(res);
            break;

        default:
            sprintf(tmp_log, "evaluate eval_prefixop ,NOT IMPLEMENTED , tokId:%d", res->id);
            mlog(tmp_log, 0, 1);
    }

    /* PUSH IT */
    return evaluate_expression(prefixop.exp);
}

int eval_postfixop(struct postfixop_s postfixop) {

    mlog("eval_postfixop() ... enter ", 2, 0);

    /* EVAL the exp == push it on the stack */

    evaluate_expression(postfixop.exp);

    struct value_s *res = seek_in_env(postfixop.exp->lit.token->value);

    /* PROCESS */
    switch (postfixop.token->id) {

        case INCREMENT:
            process_inc(res);
            break;

        case DECREMENT:
            process_dec(res);
            break;

        default:
            sprintf(tmp_log, "evaluate eval_postfixop ,NOT IMPLEMENTED , tokId:%d", res->id);
            mlog(tmp_log, 0, 1);
    }

    return INTRP_OK;
}

int eval_binaryop(struct binaryop_s binaryop) {

    mlog("eval_binaryop() ... enter", 2, 0);

    struct value_s *res = malloc(sizeof(struct value_s));

    /* PUSH IT ON STACK */
    evaluate_expression(binaryop.exp1);
    evaluate_expression(binaryop.exp2);

    //mlog("eval_binaryop stack after eval exp1,exp2:", 2,0);
    //display_stack();

    struct value_s *rd = pop_stack();
    struct value_s *rg = pop_stack();

    assert(rd != NULL);
    assert(rg != NULL);

    res->id = rg->id;

    switch (binaryop.token->id) {
        case PLUS:
            mlog("eval_binaryop: PLUS",2,0);
            switch(res->id) {
                case INTEGER:
                    res->val = rd->val + rg->val;
                    break;
                case FLOAT:
                    res->f = rd->f + rg->f;
                    break;
                case CHAR:
                    res->c = rd->c + rg->c;
                    break;
                case STRING:
                    strcpy(res->str, rg->str);
                    strcat(res->str, rd->str);
                    break;
                default:
                    sprintf(tmp_log, "evaluate PLUS not Implemented for tokenId = %d\n", res->id);
                    mlog(tmp_log, 0, 1);
                    break;
            }
            break;

        case MINUS:
            switch(res->id) {
                case INTEGER:
                    res->val = rg->val - rd->val;
                    break;
                case FLOAT:
                    res->f = rg->f - rd->f;
                    break;
                case CHAR:
                    res->c = rg->c - rd->c;
                    break;
                default:
                    sprintf(tmp_log, "evaluate MINUS not Implemented for tokenId = %d\n", res->id);
                    mlog(tmp_log, 0, 1);
                    break;
            }
            break;

        case ASTERISK:
            switch(res->id) {
                case INTEGER:
                    res->val = rg->val * rd->val;
                    break;
                case FLOAT:
                    res->f = rg->f * rd->f;
                    break;
                default:
                    sprintf(tmp_log, "evaluate ASTERISK not Implemented for tokenId = %d\n", res->id);
                    mlog(tmp_log, 0, 1);
                    break;
            }
            break;

        case EQUAL:
            mlog("eval_binaryop: EQUAL",2,0);
            res->id = BOOLEAN;
            switch(rg->id) {
                case BOOLEAN:
                    res->bool = rg->bool == rd->bool;
                    break;
                case INTEGER:
                    res->bool = rg->val == rd->val;
                    break;
                case FLOAT:
                    res->bool = rg->f == rd->f;
                    break;
                case CHAR:
                    res->bool = rg->c == rd->c;
                    break;
                case STRING:
                    res->bool = (strcmp(rg->str, rd->str) == 0);
                    break;
                default:
                    sprintf(tmp_log, "evaluate EQUAL not Implemented for tokenId = %d\n", res->id);
                    mlog(tmp_log, 0, 1);
                    break;
            }
            break;

        case LESS_THAN:
            res->id = BOOLEAN;
            switch(rg->id) {
                case BOOLEAN :
                    res->bool = rg->bool < rd->bool;
                    break;
                case INTEGER:
                    res->bool = rg->val < rd->val;
                    break;
                case FLOAT:
                    res->bool = rg->f < rd->f;
                    break;
                case CHAR:
                    res->bool = rg->c < rd->c;
                    break;
                case STRING:
                    res->bool = (strcmp(rg->str, rd->str) < 0);
                    break;
                default:
                    sprintf(tmp_log, "evaluate LESS_THAN not Implemented for tokenId = %d\n", res->id);
                    mlog(tmp_log, 0, 1);
                    break;
            }
            break;

        case LESS_OR_EQUAL:
            res->id = BOOLEAN;
            switch(rg->id) {
                case BOOLEAN:
                    res->bool = rg->bool <= rd->bool;
                    break;
                case INTEGER:
                    res->bool = rg->val <= rd->val;
                    break;
                case FLOAT:
                    res->bool = rg->f <= rd->f;
                    break;
                case CHAR:
                    res->bool = rg->c <= rd->c;
                    break;
                case STRING:
                    res->bool = (strcmp(rg->str, rd->str) <= 0);
                    break;
                default:
                    sprintf(tmp_log, "evaluate LESS_OR_EQUAL not Implemented for tokenId = %d\n", res->id);
                    mlog(tmp_log, 0, 1);
                    break;
            }
            break;

        case GREATER_THAN:
            res->id = BOOLEAN;
            switch(rg->id) {
                case BOOLEAN:
                    res->bool = rg->bool > rd->bool;
                    break;
                case INTEGER:
                    res->bool = rg->val > rd->val;
                    break;
                case FLOAT:
                    res->bool = rg->f > rd->f;
                    break;
                case CHAR:
                    res->bool = rg->c > rd->c;
                    break;
                case STRING:
                    res->bool = (strcmp(rg->str, rd->str) > 0);
                    break;
                default:
                    sprintf(tmp_log, "evaluate GREATER_THAN not Implemented for tokenId = %d\n", res->id);
                    mlog(tmp_log, 0, 1);
                    break;
            }
            break;

        case GREATER_OR_EQUAL:
            res->id = BOOLEAN;
            switch(rg->id) {
                case BOOLEAN:
                    res->bool = rg->bool >= rd->bool;
                    break;
                case INTEGER:
                    res->bool = rg->val >= rd->val;
                    break;
                case FLOAT:
                    res->bool = rg->f >= rd->f;
                    break;
                case CHAR:
                    res->bool = rg->c >= rd->c;
                    break;
                case STRING:
                    res->bool = (strcmp(rg->str, rd->str) >= 0);
                    break;
                default:
                    sprintf(tmp_log, "evaluate GREATER_OR_EQUAL not Implemented for tokenId = %d\n", res->id);
                    mlog(tmp_log, 0, 1);
                    break;
            }
            break;

        case AMPERSAND:
            switch(res->id) {
                case INTEGER:
                    res->val = rg->val & rd->val;
                    break;
                default:
                    sprintf(tmp_log, "evaluate AMPERSAND not Implemented for tokenId = %d\n", res->id);
                    mlog(tmp_log, 0, 1);
                    break;
            }
            break;

        case SHIFT_LEFT:
            switch(res->id) {
                case INTEGER:
                    res->val = rg->val << rd->val;
                    break;
                default:
                    sprintf(tmp_log, "evaluate SHIFT_LEFT not Implemented for tokenId = %d\n", res->id);
                    mlog(tmp_log, 0, 1);
                    break;
            }
            break;

        case SHIFT_RIGHT:
            switch(res->id) {
                case INTEGER:
                    res->val = rg->val >> rd->val;
                    break;
                default:
                    sprintf(tmp_log, "evaluate SHIFT_RIGHT not Implemented for tokenId = %d\n", res->id);
                    mlog(tmp_log, 0, 1);
                    break;
            }
            break;

        case SHIFT_RIGHT_UNSIGNED:
            switch(res->id) {
                case INTEGER:
                    res->val = rg->val >> rd->val;
                    break;
                default:
                    sprintf(tmp_log, "evaluate SHIFT_RIGHT_UNSIGNED not Implemented for tokenId = %d\n", res->id);
                    mlog(tmp_log, 0, 1);
                    break;
            }
            break;

        case STRICT_EQUAL:
            res->id = BOOLEAN;
            switch(rg->id) {
                case BOOLEAN:
                    res->bool = rg->bool == rd->bool;
                    break;
                case INTEGER:
                    res->bool = rg->val == rd->val;
                    break;
                case FLOAT:
                    res->bool = rg->f == rd->f;
                    break;
                case CHAR:
                    res->bool = rg->c == rd->c;
                    break;
                case STRING:
                    res->bool = (strcmp(rg->str, rd->str) == 0);
                    break;
                default:
                    sprintf(tmp_log, "evaluate STRICT_EQUAL not Implemented for tokenId = %d\n", res->id);
                    mlog(tmp_log, 0, 1);
                    break;
            }
            break;

        case LOGICAL_AND:
            res->id = BOOLEAN;
            switch(rg->id) {
                case BOOLEAN:
                    res->bool = rg->bool && rd->bool;
                    break;
                case INTEGER:
                    res->bool = rg->val && rd->val;
                    break;
                default:
                    sprintf(tmp_log, "evaluate LOGICAL_AND not Implemented for tokenId = %d\n", res->id);
                    mlog(tmp_log, 0, 1);
                    break;
            }
            break;

        case LOGICAL_XOR:
            res->id = BOOLEAN;
            switch(rg->id) {
                case BOOLEAN:
                    res->bool = rg->bool ^ rd->bool;
                    break;
                case INTEGER:
                    res->bool = rg->val ^ rd->val;
                    break;
                default:
                    sprintf(tmp_log, "evaluate LOGICAL_XOR not Implemented for tokenId = %d\n", res->id);
                    mlog(tmp_log, 0, 1);
                    break;
            }
            break;

        case LOGICAL_OR:
            res->id = BOOLEAN;
            switch(rg->id) {
                case BOOLEAN:
                    res->bool = rg->bool || rd->bool;
                    break;
                case INTEGER:
                    res->bool = rg->bool || rd->bool;
                    break;
                default:
                    sprintf(tmp_log, "evaluate LOGICAL_OR not Implemented for tokenId = %d\n", res->id);
                    mlog(tmp_log, 0, 1);
                    break;
            }
            break;

        case STRICT_NOT_EQUAL:  /* !== */
            res->id = BOOLEAN;
            switch(rg->id) {
                case BOOLEAN:
                    res->bool = rg->bool != rd->bool;
                    break;
                case INTEGER:
                    res->bool = rg->val != rd->val;
                    break;
                case FLOAT:
                    res->bool = rg->f != rd->f;
                    break;
                case CHAR:
                    res->bool = rg->c != rd->c;
                    break;
                case STRING:
                    res->bool = (strcmp(rg->str, rd->str) != 0);
                    break;
                default:
                    sprintf(tmp_log, "evaluate STRICT_NOT_EQUAL not Implemented for tokenId = %d\n", res->id);
                    mlog(tmp_log, 0, 1);
                    break;
            }
            break;

        case NOT_EQUAL:
            res->id = BOOLEAN;
            switch(rg->id) {
                case BOOLEAN:
                    res->bool = rg->bool != rd->bool;
                    break;
                case INTEGER:
                    res->bool = rg->val != rd->val;
                    break;
                case FLOAT:
                    res->bool = rg->f != rd->f;
                    break;
                case CHAR:
                    res->bool = rg->c != rd->c;
                    break;
                case STRING:
                    res->bool = strcmp(rg->str, rd->str) != 0;
                    break;
                default:
                    sprintf(tmp_log, "evaluate NOT_ASSIGNMENT not Implemented for tokenId = %d\n", res->id);
                    mlog(tmp_log, 0, 1);
                    break;
            }
            break;

        default:
            sprintf(tmp_log, "eval_binaryop_with_assign for tokenId = %d\n", res->id);
            mlog(tmp_log, 2, 0);
            return eval_binaryop_with_assign(rd, rg, binaryop.exp1, binaryop.token->id);
    }

    /* PUSH THE RES */
    push_stack(res);

    /* TODO:CHECKME */
    free(rg);
    free(rd);

    return INTRP_OK;

    /*mlog("eval_binaryop final stack:", 2,0);
    display_stack();*/
}

int eval_binaryop_with_assign(struct value_s *rd, struct value_s * rg, struct node_s* exp1, int tokenID) {

    mlog("eval_binaryop_with_assign() ... enter ", 2, 0);

    /* HAV TO BE IDENTIFIER */
    assert(exp1->lit.token->id == IDENTIFIER);

    struct value_s *res = malloc(sizeof(struct value_s));

    /* TODO:CHECK TYPE (left or right ??) */
    res->id = rg->id;

    /* CALCULATE ON RES, PUSH RES && UPDATE RIGHT_EXP */
    switch (tokenID) {

        case PLUS_ASSIGNMENT:
            switch(res->id) {
                case INTEGER:
                    res->val = rd->val + rg->val;
                    break;
                case FLOAT:
                    res->f = rd->f + rg->f;
                    break;
                case CHAR:
                    res->c = rd->c + rg->c;
                    break;
                case STRING:
                    strcpy(res->str, rg->str);
                    strcat(res->str, rd->str);
                    break;
                default:
                    sprintf(tmp_log, "evaluate PLUS_ASSIGNMENT not Implemented for tokenId = %d\n", res->id);
                    mlog(tmp_log, 0, 1);
                    break;
            }
            break;

        case MINUS_ASSIGNMENT:
            switch(res->id) {
                case INTEGER:
                    res->val = rg->val - rd->val;
                    break;
                case FLOAT:
                    res->f = rg->f - rd->f;
                    break;
                case CHAR:
                    res->c = rg->c - rd->c;
                    break;
                default:
                    sprintf(tmp_log, "evaluate MINUS_ASSIGNMENT not Implemented for tokenId = %d\n", res->id);
                    mlog(tmp_log, 0, 1);
                    break;
            }
            break;

        case DIV_ASSIGNMENT:
            switch(res->id) {
                case INTEGER:
                    res->val = rg->val / rd->val;
                    break;
                case FLOAT:
                    res->f = rg->f / rd->f;
                    break;
                case CHAR:
                    res->c = rg->c / rd->c;
                    break;
                default:
                    sprintf(tmp_log, "evaluate DIV_ASSIGNMENT not Implemented for tokenId = %d\n", res->id);
                    mlog(tmp_log, 0, 1);
                    break;
            }
            break;

        case MOD_ASSIGNMENT:
            switch(res->id) {
                case INTEGER:
                    res->val = rg->val % rd->val;
                    break;
                case CHAR:
                    res->c = rg->c % rd->c;
                    break;
                default:
                    sprintf(tmp_log, "evaluate MOD_ASSIGNMENT not Implemented for tokenId = %d\n", res->id);
                    mlog(tmp_log, 0, 1);
                    break;
            }
            break;

        case SHIFT_LEFT_ASSIGNMENT:
            switch(res->id) {
                case INTEGER:
                    res->val = rg->val << rd->val;
                    break;
                case CHAR:
                    res->c = rg->c << rd->c;
                    break;
                default:
                    sprintf(tmp_log, "evaluate SHIFT_LEFT_ASSIGNMENT not Implemented for tokenId = %d\n", res->id);
                    mlog(tmp_log, 0, 1);
                    break;
            }
            break;

        case SHIFT_RIGHT_ASSIGNMENT:
            switch(res->id) {
                case INTEGER:
                    res->val = rg->val >> rd->val;
                    break;
                case CHAR:
                    res->c = rg->c >> rd->c;
                    break;
                default:
                    sprintf(tmp_log, "evaluate SHIFT_RIGHT_ASSIGNMENT not Implemented for tokenId = %d\n", res->id);
                    mlog(tmp_log, 0, 1);
                    break;
            }
            break;

        case AND_ASSIGNMENT:
            switch(res->id) {
                case INTEGER:
                    res->val = rg->val & rd->val;
                    break;
                case CHAR:
                    res->c = rg->c & rd->c;
                    break;
                default:
                    sprintf(tmp_log, "evaluate AND_ASSIGNMENT not Implemented for tokenId = %d\n", res->id);
                    mlog(tmp_log, 0, 1);
                    break;
            }
            break;

        case XOR_ASSIGNMENT:
            switch(res->id) {
                case INTEGER:
                    res->val = rg->val ^ rd->val;
                    break;
                case CHAR:
                    res->c = rg->c ^ rd->c;
                    break;
                default:
                    sprintf(tmp_log, "evaluate XOR_ASSIGNMENT not Implemented for tokenId = %d\n", res->id);
                    mlog(tmp_log, 0, 1);
                    break;
            }
            break;

        case OR_ASSIGNMENT:
            switch(res->id) {
                case INTEGER:
                    res->val = rg->val | rd->val;
                    break;
                case CHAR:
                    res->c = rg->c | rd->c;
                    break;
                default:
                    sprintf(tmp_log, "evaluate OR_ASSIGNMENT not Implemented for tokenId = %d\n", res->id);
                    mlog(tmp_log, 0, 1);
                    break;
            }
            break;

        case SHIFT_RIGHT_UNSIGNED_ASSIGNMENT:
            switch(res->id) {
                case INTEGER:
                    res->val = rg->val >> rd->val;
                    break;
                case CHAR:
                    res->c = rg->c >> rd->c;
                    break;
                default:
                    sprintf(tmp_log, "evaluate SHIFT_RIGHT_UNSIGNED_ASSIGNMENT not Implemented for tokenId = %d\n", res->id);
                    mlog(tmp_log, 0, 1);
                    break;
            }
            break;

        /* TODO: CHEKME */
        case NOT_ASSIGNMENT:
            switch(res->id) {
                case INTEGER:
                    res->bool = rg->val != rd->val;
                    break;
                case FLOAT:
                    res->bool = rg->f != rd->f;
                    break;
                case CHAR:
                    res->bool = rg->c != rd->c;
                    break;
                case STRING:
                    res->bool = strcmp(rg->str, rd->str) != 0;
                    break;
                default:
                    sprintf(tmp_log, "evaluate NOT_ASSIGNMENT not Implemented for tokenId = %d\n", res->id);
                    mlog(tmp_log, 0, 1);
                    break;
            }
            break;

        case ASSIGNMENT:
            switch(res->id) {
                case INTEGER:
                    res->val = rd->val;
                    break;
                case FLOAT:
                    res->f = rd->f;
                    break;
                case CHAR:
                    res->c =  rd->c;
                    break;
                case STRING:
                    strcpy(res->str, rd->str);
                    break;
                default:
                    sprintf(tmp_log, "evaluate ASSIGNMENT not Implemented for tokenId = %d\n", res->id);
                    mlog(tmp_log, 0, 1);
                    break;
            }
            break;

        case EXPONENTIATION:
            sprintf(tmp_log, "evaluate EXPONENTIATION not Implemented for tokenId = %d\n", res->id);
            mlog(tmp_log, 0, 1);

        default:
            mlog("ERROR BINARY OP", 0, 1);
    }

    /* TODO:CHECKME UPDATE  */
    struct value_s* tmp_rg = seek_in_env(exp1->lit.token->value);
    assert(tmp_rg != NULL);
    memcpy(tmp_rg, res, sizeof(struct value_s));

    /* EVALUTE && PUSH */
    push_stack(res);

    /* TODO:CHECKME */
    free(rg);
    free(rd);

    return INTRP_OK;
}


int eval_call(struct call_s call) {

    mlog("eval_call() ... enter", 2, 0);
    /*display_env();
    display_stack();*/

    /* Sorry FOr this, but catching print funct..... */
    if (strcmp(call.func->func.token->value, "print") == 0) {
        evaluate_expression(call.args->value);
        print_value(pop_stack());
        return INTRP_OK;
    }

    struct value_s *f = seek_in_env(call.func->func.token->value);

    /* the func is defined */
    if (f != NULL) {

        struct list_node_s *f_bdy = f->func.body;
        struct list_token_s *f_args = f->func.args;

        /* ARGS */
        if (f_args->tok != NULL) {
            mlog("CALL FUNC WITH ARGS", 2, 0);

            struct list_node_s *call_args = call.args;
            int nb_args = 0;

            /* PUSH call args ON STACK */
            while (call_args != NULL) {
                assert(evaluate_expression(call_args->value) != INTRP_ERR);
                call_args = call_args->next;
                nb_args++;
            }

            /* create new env */
            table_create(256);

            /* update bos to include args */
            env_local->bos_local -= nb_args;

            nb_args = 0;
            while (f_args != NULL) {
                table_add(env_local, f_args->tok->value, (void*)(long int) (env_local->bos_local+ (nb_args++)));
                f_args = f_args->next;
            }

            assert(env_local->bos_local + nb_args == tos); /* TODO: check tos ? tos-1 */
        }

        mlog("eval_call: display after process args:",2,0);
        display_env();
        display_stack();

        int res = evaluate_env(f_bdy);

        mlog("call .. print_stack before destroy (after evalaute):", 2,0);
        display_stack();
        display_env();

        /* void function */
        if (res != INTRP_RETURN) {
            /* free env && push NULL */
            table_destroy(env_local);
            push_stack(NULL);
        }
        else {
            /* store the return && free env */

            struct  value_s * tmp = pop_stack();
            /*sprintf(tmp_log,"call: pop_tmp: %p, id:%d",tmp, tmp->id);
            mlog(tmp, 2,0);*/
            table_destroy(env_local);

            /*mlog("call .. print_stack after destroy:", 2,0);
            display_stack();
            display_env();*/

            /*sprintf(tmp_log,"call: push_tmp: %p, id:%d",tmp, tmp->id);
            mlog(tmp, 2,0);*/
            push_stack(tmp);
        }

        /*
        mlog("call .. print_stack after pushing the ret:", 2,0);
        display_stack();
        display_env();
         */

    } else {
        sprintf(tmp_log, "calling undefined func = %s ", f->func.token->value);
        mlog(tmp_log, 0, 1);
    }

    return INTRP_OK;
}

int eval_funct(struct func_s func) {

    mlog("eval_funct() ... enter ", 2, 0);

    struct value_s *res = malloc(sizeof(struct value_s));

    res->id = func.token->id;
    res->func = func;

    /* ADD to env && PUSH */
    push_stack(res);
    table_add(env_local, func.token->value, (void*)(long int) (tos-1));

    /* PUSH NULL */
    struct  value_s * copy = malloc(sizeof(struct value_s));
    memcpy(copy,res, sizeof(struct value_s));
    push_stack(copy);

    return INTRP_OK;
}

int eval_ternary(struct ternary_s ternary) {

    mlog("eval_ternary", 2, 0);

    struct node_s *thn = ternary.thn;
    struct node_s *els = ternary.els;
    int res;

    /* PUSH IT */
    evaluate_expression(ternary.condition);

    /* POP IT */
    struct value_s *cond = pop_stack();

    if (cond->bool) {
        res = evaluate_expression(thn);
    } else {
        res = evaluate_expression(els);
    }

    /* TODO:CHECKME */
    free(cond);

    return res;
}

int eval_var1(struct var1_s var1) {

    mlog("eval_var1", 2, 0);

    /*  PUSH IT */
    push_stack(NULL);

    /* ADD To ENV */
    table_add(env_local, var1.token->value, (void*)(long int) (tos-1));

    return INTRP_OK;
}

int eval_var2(struct var2_s var2) {

    mlog("eval_var2", 2, 0);

    /* PUSH IT */
    int res = evaluate_expression(var2.exp);

    sprintf(tmp_log, "eval_var2, res = %d",res);
    mlog(tmp_log,2,0);

    /* ADD TO ENV */
    table_add(env_local, var2.token->value, (void*)(long int) (tos-1));

    return res;
}

int eval_return1(struct return_s ret) {

    sprintf(tmp_log, "eval_return1: expNodeId:%d", ret.exp->id);
    mlog(tmp_log, 2, 0);

    push_stack(NULL);

    return INTRP_RETURN;
}

int eval_return2(struct return_s ret) {

    sprintf(tmp_log, "eval_return2: expNodeId:%d", ret.exp->id);
    mlog(tmp_log, 2, 0);

    /* PUSH */
    evaluate_expression(ret.exp);

    return INTRP_RETURN;
}

int eval_ifthenelse(struct ifthenelse_s ifthenelse) {

    mlog("eval_ifthenelse enter ...", 2,0);

    struct list_node_s *thn = ifthenelse.thn;
    struct list_node_s *els = ifthenelse.els;
    int res;

    /* eval COND && PUSH */
    assert (evaluate_expression(ifthenelse.exp) != INTRP_ERR);

    mlog("eval_ifthenelse stack:", 2,0);
    display_stack();

    /* POP IT */
    struct value_s *cond = pop_stack();

    if (cond->bool) {
        res = evaluate_env(thn);
    } else {
        res = evaluate_env(els);
    }

    /* TODO:CHECKME */
    free(cond);

    return res;
}

int eval_while(struct while_s whl) {

    mlog("eval_while() ... enter", 2, 0);
    /*display_env();*/

    struct list_node_s *tmp = whl.body;
    int res;

    /* eval COND && PUSH */
    evaluate_expression(whl.condition);

    /* POP IT */
    struct value_s *cond = pop_stack();

    assert(cond != NULL);

    while (cond->bool) {

        res = evaluate_env(tmp);

        switch (res) {

            case INTRP_RETURN:
                return res;

            case INTRP_BREAK:
                return INTRP_BREAK;

            case INTRP_CONTINUE:
            case INTRP_OK:
                /* re-loop */
                evaluate_expression(whl.condition);
                cond = pop_stack();
                tmp = whl.body;
                break;

            default:
                mlog("eval_while(): eval body: default !!!!! ", 0, 1);
        }
    }

    sprintf(tmp_log, " !!! eval_while (break_exit) .... res = %d",res);
    mlog(tmp_log,2,0);

    /* TODO:CHECKME */
    free(cond);

    return INTRP_OK;
}

int eval_branch(struct branch_s branch) {

    mlog("eval_branch() ... enter", 2, 0);

    switch( branch.tok->id) {

        case BREAK:
            return INTRP_BREAK;

        case CONTINUE:
            return INTRP_CONTINUE;

        default:
            mlog("eval_branch: SHOULD NEVER HAPPEN !!!",0,0);
            return INTRP_ERR;
    }
}