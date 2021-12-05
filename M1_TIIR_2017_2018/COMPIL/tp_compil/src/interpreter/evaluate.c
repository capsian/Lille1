#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "lexer/symbol.h"
#include "interpreter/global_environnement.h"
#include "interpreter/structs.h"
#include "interpreter/evaluate.h"


void evaluate_env(struct list_node_s* list_node) {

    struct value_s* res;
    struct list_node_s* tmp = list_node;
    struct environnement_s* env_global = put("init",NULL,env_global);

    while (tmp != NULL) {
        res = evaluate(tmp->value, env_global);
        print_value(res);
        tmp = tmp->next;
    }
}

void print_value(struct value_s* res) {

    if (res == NULL) {
        printf("value: NULL \n");
        return;
    }

    switch (res->id) {
        case INTEGER:
            printf("value: int = %d\n",res->val);
            break;
        case FLOAT:
            printf("value: float = %f\n",res->f);
            break;
        case STRING:
            printf("value: string = %s\n",res->str);
            break;
        case CHAR:
            printf("value: char = %c\n",res->c);
            break;
    }
}

struct value_s* evaluate(struct node_s* node, struct environnement_s* env_global) {

    switch (node->id) {

        case 0: /* LIT */
            return eval_litteral(node->lit, env_global);
        case 1: /* PrefixOP */
            return eval_prefixop(node->prefixop, env_global);
        case 2: /* POSTFIX */
            return eval_postfixop(node->postfixop, env_global);
        case 3: /* BINARYOP */
            return eval_binaryop(node->binaryop, env_global);
        case 4: /* CALL */
            return eval_call(node->call, env_global);
        case 5: /* FUNCTION */
            return eval_funct(node->func, env_global);
        case 6: /* FUNCTION */
            return eval_funct(node->func, env_global);  /* TODO CHECK !! */
        case 7: /* TERNARY */
            return eval_ternary(node->ternary, env_global);

        case 16:    /* VAR1 */
            return eval_var1(node->var1, env_global);
        case 17:    /* VAR2 */
            return eval_var2(node->var2, env_global);
        case 18: /* RETURN */
            return eval_return1(node->ret, env_global);
        case 19:    /* RETURN */
            return eval_return2(node->ret, env_global); /* TODO CHECK !! */
        case 20:    /* IfThenElse */
            return eval_ifthenelse(node->ifthenelse, env_global);
        case 21:    /* WHILE */
            return eval_while(node->whil, env_global);
        default:
            printf("evaluate() default !!! SHOULD NEVER HAPPEN !! nodeId = %d\n", node->id);
            exit(EXIT_FAILURE);
    }

}

struct value_s* eval_litteral(struct literal_s lit, struct environnement_s* env_global) {

    struct value_s* res = malloc(sizeof(struct value_s));

    switch (lit.token->id) {
        case INTEGER:
            res->id = lit.token->id;
            res->val = atoi(lit.token->value);
            return res;
        case IDENTIFIER:
            free(res);
            return get(lit.token->value, env_global);
        case STRING:
            res->id = lit.token->id;
            strcpy(res->str,lit.token->value);
            return res;
        default:
            free(res);
            printf("evaluate LIT NOT IMPLEMENTED, id = %d\n",res->id);
            // return NULL;
            exit(EXIT_FAILURE);
    }
}

struct value_s* eval_prefixop(struct prefixop_s prefixop, struct environnement_s* env_global) {

    struct value_s* res = NULL;

    switch (prefixop.token->id) {
        case INCREMENT:
            /* check if tok is LIT */
            if (prefixop.exp->lit.token->id == IDENTIFIER)
                res = get(prefixop.exp->lit.token->value, env_global);

            if (res != NULL) {
                ++res->val;
                return res;
            }
            else
                printf("eval_prefixop(), NOT IDENTIFIER || UNDEFINED IN ENV !! \n");

            break;
        case DECREMENT:

            /* check if tok is LIT */
            if (prefixop.exp->lit.token->id == IDENTIFIER)
                res = get(prefixop.exp->lit.token->value, env_global);

            if (res != NULL) {
                --res->val;
                return res;
            }
            else
                printf("eval_prefixop(), NOT IDENTIFIER || UNDEFINED IN ENV !! \n");

            break;
        default:
            printf("evaluate LIT NOT IMPLEMENTED, id = %d\n",res->id);
            // return NULL;
            exit(EXIT_FAILURE);
    }

    return res;
}

struct value_s* eval_postfixop(struct postfixop_s postfixop, struct environnement_s* env_global) {

    struct value_s* res = malloc(sizeof(struct value_s));
    struct value_s* old = NULL;

    switch (postfixop.token->id) {
        case INCREMENT:
            /* check if tok is LIT */
            if (postfixop.exp->lit.token->id == IDENTIFIER)
                old = get(postfixop.exp->lit.token->value, env_global);

            if (old != NULL) {

                /* init res */
                res->id = old->id;

                /* INTEGER */
                if (old->id == INTEGER) {
                    res->val = old->val + 1;
                    put(postfixop.exp->lit.token->value,res,env_global);
                }
                /* FLOAT */
                else if ( old->id == FLOAT) {
                    res->f = old->f + 1;
                    put(postfixop.exp->lit.token->value,res,env_global);
                }

                return old;
            }
            else
                printf("eval_postfixop(), NOT IDENTIFIER || UNDEFINED IN ENV 1 !! \n");

            break;
        case DECREMENT:

            if (postfixop.exp->lit.token->id == IDENTIFIER)
                old = get(postfixop.exp->lit.token->value, env_global);

            if (old != NULL) {

                /* init res */
                res->id = old->id;

                /* INTEGER */
                if (old->id == INTEGER) {
                    res->val = old->val - 1;
                    put(postfixop.exp->lit.token->value, res, env_global);
                }
                    /* FLOAT */
                else if (old->id == FLOAT) {
                    res->f = old->f - 1;
                    put(postfixop.exp->lit.token->value, res, env_global);
                }

                return old;
            }
            else
                printf("eval_postfixop(), NOT IDENTIFIER || UNDEFINED IN ENV 2 !! \n");

            break;
        default:
            printf("evaluate POSTFIX NOT IMPLEMENTED, id = %d\n",res->id);
            // return NULL;
            exit(EXIT_FAILURE);
    }

    return res;
}

void* get_value(struct value_s* val) {

    if (val->id == FLOAT)
        return (void *) &val->f;
    else if (val->id == INTEGER)
        return (void*) &val->val;
    else if (val->id == CHAR)
        return (void*) &val->c;
    else if (val->id == STRING)
        return (void*) val->str;
    else
        exit(EXIT_FAILURE);
}

struct value_s* process_binaryop(struct value_s* rg, struct value_s* rd,  unsigned int tokenId) {

    struct value_s* res = malloc(sizeof(struct value_s));

    res->id = rg->id;

    void* value_a = get_value(rg);
    void* value_b = get_value(rd);

    switch (tokenId) {

        case PLUS:
            if (res->id == FLOAT)
                res->f = *((float*)value_a) + *((float*) value_b);
            else if (res->id == INTEGER)
                res->val = *((int*)value_a) + *((int*) value_b);
            else if (res->id == CHAR)
                res->c = *((char*)value_a) + *((char*) value_b);
            else if (res->id == STRING) {
                strcpy(res->str, (char*) value_a);
                strcat(res->str, (char*) value_b);
            }
            else {
                printf("evaluate PLUS not Implemented for tokenId = %d\n", tokenId);
                exit(EXIT_FAILURE);
            }
            break;

        case MINUS:
            if (res->id == FLOAT)
                res->f = *((float*)value_a) - *((float*) value_b);
            else if (res->id == INTEGER)
                res->val = *((int*)value_a) - *((int*) value_b);
            else if (res->id == CHAR)
                res->c = *((char*)value_a) - *((char*) value_b);
            else {
                printf("evaluate MINUS not Implemented for tokenId = %d\n", tokenId);
                exit(EXIT_FAILURE);
            }
            break;

        case ASTERISK:
            if (res->id == FLOAT)
                res->f = *((float*)value_a) * *((float*) value_b);
            else if (res->id == INTEGER)
                res->val = *((int*)value_a) * *((int*) value_b);
            else if (res->id == CHAR)
                res->c = *((char*)value_a) * *((char*) value_b);
            else {
                printf("evaluate ASTERISK not Implemented for tokenId = %d\n", tokenId);
                exit(EXIT_FAILURE);
            }
            break;

        case EQUAL:
            if (res->id == FLOAT)
                res->bool = *((float*)value_a) == *((float*) value_b);
            else if (res->id == INTEGER)
                res->bool = *((int*)value_a) == *((int*) value_b);
            else if (res->id == CHAR)
                res->bool = *((char*)value_a) == *((char*) value_b);
            else if (res->id == STRING) {
                res->bool = strcmp((char*)value_a,(char*)value_b) == 0;
            }
            else {
                printf("evaluate EQUAL not Implemented for tokenId = %d\n", tokenId);
                exit(EXIT_FAILURE);
            }
            break;

        case LESS_THAN:
            printf("LESS_THAN: tokId=%d\n", res->id);
            if (res->id == FLOAT)
                res->bool = *((float*)value_a) < *((float*) value_b);
            else if (res->id == INTEGER)
                res->bool = *((int*)value_a) < *((int*) value_b);
            else if (res->id == CHAR)
                res->bool = *((char*)value_a) < *((char*) value_b);
            else if (res->id == STRING) {
                res->bool = strcmp((char*)value_a,(char*)value_b) < 0;
            }
            else {
                printf("evaluate LESS_THAN not Implemented for tokenId = %d\n", tokenId);
                exit(EXIT_FAILURE);
            }
            break;

        case LESS_OR_EQUAL:
            if (res->id == FLOAT)
                res->bool = *((float*)value_a) <= *((float*) value_b);
            else if (res->id == INTEGER)
                res->bool = *((int*)value_a) <= *((int*) value_b);
            else if (res->id == CHAR)
                res->bool = *((char*)value_a) <= *((char*) value_b);
            else if (res->id == STRING) {
                res->bool = strcmp((char*)value_a,(char*)value_b) <= 0;
            }
            else {
                printf("evaluate LESS_OR_EQUAL not Implemented for tokenId = %d\n", tokenId);
                exit(EXIT_FAILURE);
            }
            break;

        case GREATER_THAN:
            if (res->id == FLOAT)
                res->bool = *((float*)value_a) > *((float*) value_b);
            else if (res->id == INTEGER)
                res->bool = *((int*)value_a) > *((int*) value_b);
            else if (res->id == CHAR)
                res->bool = *((char*)value_a) > *((char*) value_b);
            else if (res->id == STRING) {
                res->bool = strcmp((char*)value_a,(char*)value_b) > 0;
            }
            else {
                printf("evaluate GREATER_THAN not Implemented for tokenId = %d\n", tokenId);
                exit(EXIT_FAILURE);
            }
            break;

        case GREATER_OR_EQUAL:
            if (res->id == FLOAT)
                res->bool = *((float*)value_a) >= *((float*) value_b);
            else if (res->id == INTEGER)
                res->bool = *((int*)value_a) >= *((int*) value_b);
            else if (res->id == CHAR)
                res->bool = *((char*)value_a) >= *((char*) value_b);
            else if (res->id == STRING) {
                res->bool = strcmp((char*)value_a,(char*)value_b) >= 0;
            }
            else {
                printf("evaluate GREATER_OR_EQUAL not Implemented for tokenId = %d\n", tokenId);
                exit(EXIT_FAILURE);
            }
            break;

        case AMPERSAND:
            if (res->id == INTEGER)
                res->val = *((int*)value_a) & *((int*) value_b);
            else {
                printf("evaluate AMPERSAND not Implemented for tokenId = %d\n", tokenId);
                exit(EXIT_FAILURE);
            }
            break;

        case SHIFT_LEFT:
            if (res->id == INTEGER)
                res->val = *((int*)value_a) >> *((int*) value_b);
            else {
                printf("evaluate SHIFT_LEFT not Implemented for tokenId = %d\n", tokenId);
                exit(EXIT_FAILURE);
            }
            break;

        case SHIFT_RIGHT:
            if (res->id == INTEGER)
                res->val = *((int*)value_a) << *((int*) value_b);
            else {
                printf("process_binaryop error 5\n");
                exit(EXIT_FAILURE);
            }
            break;

        case SHIFT_RIGHT_UNSIGNED:
            if (res->id == INTEGER)
                res->val = *((int*)value_a) >> *((int*) value_b);
            else {
                printf("process_binaryop error 6\n");
                exit(EXIT_FAILURE);
            }
            break;

        case STRICT_EQUAL:
            if (res->id == FLOAT)
                res->bool = *((float*)value_a) == *((float*) value_b);
            else if (res->id == INTEGER)
                res->bool = *((int*)value_a) == *((int*) value_b);
            else if (res->id == CHAR)
                res->bool = *((char*)value_a) == *((char*) value_b);
            else if (res->id == STRING) {
                res->bool = strcmp((char*)value_a,(char*)value_b) == 0;
            }
            else {
                printf("evaluate STRICT_EQUAL not Implemented for tokenId = %d\n", tokenId);
                exit(EXIT_FAILURE);
            }
            break;

        case LOGICAL_AND:
            if (res->id == INTEGER)
                res->bool = *((int*)value_a) && *((int*) value_b);
            else if (res->id == CHAR)
                res->bool = *((char*)value_a) && *((char*) value_b);
            else {
                printf("evaluate LOGICAL_AND not Implemented for tokenId = %d\n", tokenId);
                exit(EXIT_FAILURE);
            }
            break;

        case LOGICAL_XOR:
            if (res->id == INTEGER)
                res->bool = *((int*)value_a) ^ *((int*) value_b);
            else if (res->id == CHAR)
                res->bool = *((char*)value_a) ^ *((char*) value_b);
            else {
                printf("evaluate LOGICAL_XOR not Implemented for tokenId = %d\n", tokenId);
                exit(EXIT_FAILURE);
            }
            break;

        case LOGICAL_OR:
            if (res->id == INTEGER)
                res->bool = *((int*)value_a) || *((int*) value_b);
            else if (res->id == CHAR)
                res->bool = *((char*)value_a) || *((char*) value_b);
            else {
                printf("evaluate LOGICAL_OR not Implemented for tokenId = %d\n", tokenId);
                exit(EXIT_FAILURE);
            }
            break;

        case STRICT_NOT_EQUAL:  /* !== */
            if (res->id == FLOAT)
                res->bool = *((float*)value_a) != *((float*) value_b);
            else if (res->id == INTEGER)
                res->bool = *((int*)value_a) != *((int*) value_b);
            else if (res->id == CHAR)
                res->bool = *((char*)value_a) != *((char*) value_b);
            else if (res->id == STRING) {
                res->bool = strcmp((char*)value_a,(char*)value_b) == 0;
            }
            else {
                printf("evaluate STRICT_NOT_EQUAL not Implemented for tokenId = %d\n", tokenId);
                exit(EXIT_FAILURE);
            }
            break;

        case PLUS_ASSIGNMENT:
            if (res->id == FLOAT)
                *((float*)value_a) += *((float*) value_b);
            else if (res->id == INTEGER)
                *((int*)value_a) += *((int*) value_b);
            else if (res->id == CHAR)
                *((char*)value_a) += *((char*) value_b);
            else if (res->id == STRING) {
                strcat((char*) value_a, (char*) value_b);
            }
            else {
                printf("evaluate PLUS_ASSIGNMENT not Implemented for tokenId = %d\n", tokenId);
                exit(EXIT_FAILURE);
            }

            free(res);
            return rg;

        case MINUS_ASSIGNMENT:
            if (res->id == FLOAT)
                *((float*)value_a) -= *((float*) value_b);
            else if (res->id == INTEGER)
                *((int*)value_a) -= *((int*) value_b);
            else if (res->id == CHAR)
                *((char*)value_a) -= *((char*) value_b);
            else {
                printf("evaluate MINUS_ASSIGNMENT not Implemented for tokenId = %d\n", tokenId);
                exit(EXIT_FAILURE);
            }

            free(res);
            return rg;

        case DIV_ASSIGNMENT:
            if (res->id == FLOAT)
                *((float*)value_a) /= *((float*) value_b);
            else if (res->id == INTEGER)
                *((int*)value_a) /= *((int*) value_b);
            else if (res->id == CHAR)
                *((char*)value_a) /= *((char*) value_b);
            else {
                printf("evaluate DIV_ASSIGNMENT not Implemented for tokenId = %d\n", tokenId);
                exit(EXIT_FAILURE);
            }

            free(res);
            return rg;

        case MOD_ASSIGNMENT:
            if (res->id == INTEGER)
                *((int*)value_a) %= *((int*) value_b);
            else if (res->id == CHAR)
                *((char*)value_a) %= *((char*) value_b);
            else {
                printf("evaluate MOD_ASSIGNMENT not Implemented for tokenId = %d\n", tokenId);
                exit(EXIT_FAILURE);
            }

            free(res);
            return rg;

        case SHIFT_LEFT_ASSIGNMENT:
            if (res->id == INTEGER)
                *((int*)value_a) <<= *((int*) value_b);
            else if (res->id == CHAR)
                *((char*)value_a) <<= *((char*) value_b);
            else {
                printf("evaluate SHIFT_LEFT_ASSIGNMENT not Implemented for tokenId = %d\n", tokenId);
                exit(EXIT_FAILURE);
            }

            free(res);
            return rg;

        case SHIFT_RIGHT_ASSIGNMENT:
            if (res->id == INTEGER)
                *((int*)value_a) >>= *((int*) value_b);
            else if (res->id == CHAR)
                *((char*)value_a) >>= *((char*) value_b);
            else {
                printf("evaluate SHIFT_RIGHT_ASSIGNMENT not Implemented for tokenId = %d\n", tokenId);
                exit(EXIT_FAILURE);
            }

            free(res);
            return rg;

        case AND_ASSIGNMENT:
            if (res->id == INTEGER)
                *((int*)value_a) &= *((int*) value_b);
            else if (res->id == CHAR)
                *((char*)value_a) &= *((char*) value_b);
            else {
                printf("evaluate AND_ASSIGNMENT not Implemented for tokenId = %d\n", tokenId);
                exit(EXIT_FAILURE);
            }

            free(res);
            return rg;

        case XOR_ASSIGNMENT:
            if (res->id == INTEGER)
                *((int*)value_a) ^= *((int*) value_b);
            else if (res->id == CHAR)
                *((char*)value_a) ^= *((char*) value_b);
            else {
                printf("evaluate XOR_ASSIGNMENT not Implemented for tokenId = %d\n", tokenId);
                exit(EXIT_FAILURE);
            }

            free(res);
            return rg;

        case OR_ASSIGNMENT:
            if (res->id == INTEGER)
                *((int*)value_a) |= *((int*) value_b);
            else if (res->id == CHAR)
                *((char*)value_a) |= *((char*) value_b);
            else {
                printf("evaluate XOR_ASSIGNMENT not Implemented for tokenId = %d\n", tokenId);
                exit(EXIT_FAILURE);
            }

            free(res);
            return rg;

        case SHIFT_RIGHT_UNSIGNED_ASSIGNMENT:
            if (res->id == INTEGER)
                *((int*)value_a) >>= *((int*) value_b);
            else if (res->id == CHAR)
                *((char*)value_a) >>= *((char*) value_b);
            else {
                printf("evaluate XOR_ASSIGNMENT not Implemented for tokenId = %d\n", tokenId);
                exit(EXIT_FAILURE);
            }

            free(res);
            return rg;

        case NOT_ASSIGNMENT:
            if (res->id == FLOAT)
                res->bool = *((float*)value_a) != *((float*) value_b);
            else if (res->id == INTEGER)
                res->bool = *((int*)value_a) != *((int*) value_b);
            else if (res->id == CHAR)
                res->bool = *((char*)value_a) != *((char*) value_b);
            else if (res->id == STRING) {
                res->bool = strcmp((char*)value_a,(char*)value_b) == 0;
            }
            else {
                printf("evaluate STRICT_NOT_EQUAL not Implemented for tokenId = %d\n", tokenId);
                exit(EXIT_FAILURE);
            }
            break;

        case EXPONENTIATION:
            /*if (res->id == FLOAT)
                res->f = powf( *((float*)value_a), *((float*) value_b));
            else if (res->id == INTEGER)
                res->val = pow(*((int*)value_a), *((int*) value_b));
            else {*/
                printf("evaluate EXPONENTIATION not Implemented for tokenId = %d\n", tokenId);
                exit(EXIT_FAILURE);
            /*}*/
            break;

        case NOT_EQUAL:
            if (res->id == FLOAT)
                res->bool = *((float*)value_a) != *((float*) value_b);
            else if (res->id == INTEGER)
                res->bool = *((int*)value_a) != *((int*) value_b);
            else if (res->id == CHAR)
                res->bool = *((char*)value_a) != *((char*) value_b);
            else if (res->id == STRING) {
                res->bool = strcmp((char*)value_a,(char*)value_b) != 0;
            }
            else {
                printf("evaluate NOT_EQUAL not Implemented for tokenId = %d\n", tokenId);
                exit(EXIT_FAILURE);
            }
            break;


        default:
            printf("ERROR BINARY OP \n");
            exit(EXIT_FAILURE);
    }

    return res;
}

struct value_s* eval_binaryop(struct binaryop_s binaryop, struct environnement_s* env_global) {

    struct value_s* rg = evaluate(binaryop.exp1,env_global);
    struct value_s* rd = evaluate(binaryop.exp2,env_global);

    return process_binaryop(rg,rd,binaryop.token->id);
}

struct value_s* eval_call(struct call_s call, struct environnement_s* env_global) {

    struct value_s* f = get(call.func->func.token->value, env_global);
    struct list_node_s* call_args = call.args;

    /* the func is defined */
    if ( f != NULL) {

        struct list_node_s* f_bdy = f->func.body;
        struct list_token_s* f_args = f->func.args;

        printf("call_args: f_args:%d\n", call_args->value->id);

        /* NO ARGS */
        if (f_args.tok == NULL) {

            while (f_bdy != NULL) {
                evaluate(f_bdy->value, env_global);
                f_bdy = f_bdy->next;
            }

        } else {
            printf("CALL FUNC WITH ARGS\n");
        }

    } else {
        printf("ERROR calling undefined func = %s \n",f->func.token->value);
        exit(EXIT_FAILURE);
    }

    return NULL;
}
struct value_s* eval_funct(struct func_s func, struct environnement_s* env_global) {

    struct value_s* res = malloc(sizeof(struct value_s));

    res->id = func.token->id;
    res->func = func;

    put(func.token->value, res, env_global);

    return NULL;
}

struct value_s* eval_ternary(struct ternary_s ternary, struct environnement_s* env_global) {

    struct list_node_s* thn = ternary.thn;
    struct list_node_s* els = ternary.els;

    if ( evaluate(ternary.condition, env_global)->val ) {

        while (thn != NULL) {
            evaluate(thn->value, env_global);
            thn = thn->next;
        }
    }
    else {

        while (els != NULL) {
            evaluate(els->value, env_global);
            els = els->next;
        }
    }

    return NULL;
}

struct value_s* eval_var1(struct var1_s var1, struct environnement_s* env_global) {

    put(var1.token->value, NULL, env_global);

    return NULL;

}

struct value_s* eval_var2(struct var2_s var2, struct environnement_s* env_global) {

    put(var2.token->value,evaluate(var2.exp,env_global), env_global);

    return NULL;
}

struct value_s* eval_return1(struct return_s ret, struct environnement_s* env_global) {

    printf("eval_return1: expNodeId:%d\n", ret.exp->id);

    switch (ret.exp->id) {

    }
    return NULL;

}

struct value_s* eval_return2(struct return_s ret, struct environnement_s* env_global) {

    return evaluate(ret.exp, env_global);
}

struct value_s* eval_ifthenelse(struct ifthenelse_s ifthenelse, struct environnement_s* env_global) {


    struct list_node_s* thn = ifthenelse.thn;
    struct list_node_s* els = ifthenelse.els;

    if ( evaluate(ifthenelse.exp, env_global)->val ) {

        while (thn != NULL) {
            evaluate(thn->value, env_global);
            thn = thn->next;
        }
    }
    else {

        while (els != NULL) {
            evaluate(els->value, env_global);
            els = els->next;
        }
    }

    return NULL;
}

struct value_s* eval_while(struct while_s whl, struct environnement_s* env_global) {


    struct list_node_s* tmp = whl.body;


    while ( evaluate(whl.condition, env_global)->val ) {

        while (tmp != NULL) {
            evaluate(tmp->value, env_global);
            tmp = tmp->next;
        }

        tmp = whl.body;
    }

    return NULL;
}