#ifndef EVALUATE_H
#define EVALUATE_H


void evaluate_env(struct list_node_s* list_node);
struct value_s* evaluate(struct node_s* node, struct environnement_s* env_global);
void print_value(struct value_s* res);

struct value_s* eval_litteral(struct literal_s lit, struct environnement_s* env_global);
struct value_s* eval_prefixop(struct prefixop_s prefixop, struct environnement_s* env_global);
struct value_s* eval_postfixop(struct postfixop_s postfixop, struct environnement_s* env_global);
struct value_s* eval_binaryop(struct binaryop_s binaryop, struct environnement_s* env_global);
struct value_s* eval_call(struct call_s call, struct environnement_s* env_global);
struct value_s* eval_funct(struct func_s func, struct environnement_s* env_global);
struct value_s* eval_ternary(struct ternary_s ternary, struct environnement_s* env_global);
struct value_s* eval_var1(struct var1_s var1, struct environnement_s* env_global);
struct value_s* eval_var2(struct var2_s var2, struct environnement_s* env_global);
struct value_s* eval_return1(struct return_s ret, struct environnement_s* env_global);
struct value_s* eval_return2(struct return_s ret, struct environnement_s* env_global);
struct value_s* eval_ifthenelse(struct ifthenelse_s ifthenelse, struct environnement_s* env_global);
struct value_s* eval_while(struct while_s whl, struct environnement_s* env_global);

#endif