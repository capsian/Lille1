#ifndef EVALUATE_H
#define EVALUATE_H

enum {
    INTRP_RETURN,
    INTRP_BREAK,
    INTRP_CONTINUE,
    INTRP_OK,
    INTRP_ERR
}RET_CODE;

int evaluate_env(struct list_node_s* list_node);
int evaluate_statement(struct node_s *node);
int evaluate_expression(struct node_s *node);
void print_value(struct value_s *res);

int eval_litteral(struct literal_s lit);
int eval_prefixop(struct prefixop_s prefixop);
int eval_postfixop(struct postfixop_s postfixop);
int eval_binaryop(struct binaryop_s binaryop);
int eval_binaryop_with_assign(struct value_s *rd, struct value_s * rg, struct node_s* exp1, int tokenID);
int eval_call(struct call_s call);
int eval_funct(struct func_s func);
int eval_ternary(struct ternary_s ternary);
int eval_var1(struct var1_s var1);
int eval_var2(struct var2_s var2);
int eval_return1(struct return_s ret);
int eval_return2(struct return_s ret);
int eval_ifthenelse(struct ifthenelse_s ifthenelse);
int eval_while(struct while_s whl);
int eval_branch(struct branch_s branch);

#endif