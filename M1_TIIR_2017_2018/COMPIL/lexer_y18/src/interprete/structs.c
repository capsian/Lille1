#include <stdlib.h>

#include "interprete/defines.h"
#include "interprete/structs.h"
#include "utils.h"

struct node_s * init_litteral(struct token_s * token){
  struct node_s * new_litteral = (struct node_s *)malloc(sizeof(struct node_s));
  new_litteral->id = LITERAL;
  new_litteral->lit.token =  token;
  return new_litteral;
}

struct node_s * init_prefixop(struct token_s * token,struct node_s * exp){
  struct node_s * new_prefixop = (struct node_s *)malloc(sizeof(struct node_s));
  new_prefixop->id = PREFIXOP;
  new_prefixop->prefixop.token =  token;
  new_prefixop->prefixop.exp =  exp;
  return new_prefixop;
}

struct node_s * init_postfixop(struct token_s * token,struct node_s * exp){
  struct node_s * new_postfixop = (struct node_s *)malloc(sizeof(struct node_s));
  new_postfixop->id = POSTFIXOP;
  new_postfixop->postfixop.token =  token;
  new_postfixop->postfixop.exp =  exp;
  return new_postfixop;
}

struct node_s * init_binaryop(struct token_s * token,struct node_s * exp1,struct node_s * exp2){
  struct node_s * new_binaryop = (struct node_s *)malloc(sizeof(struct node_s));
  new_binaryop->id = BINARYOP;
  new_binaryop->binaryop.token =  token;
  new_binaryop->binaryop.exp1 =  exp1;
  new_binaryop->binaryop.exp2 =  exp2;
  return new_binaryop;
}

struct node_s * init_call(struct node_s * func,struct list_node_s* args){
  struct node_s * new_call = (struct node_s *)malloc(sizeof(struct node_s));
  new_call->id = CALL;
  new_call->call.func =  func;
  new_call->call.args = args;
  return new_call;
}

struct node_s * init_funct(struct token_s * token,struct list_token_s* args,struct list_node_s* body){

  struct node_s * new_funct = (struct node_s *)malloc(sizeof(struct node_s));

  if (token == NULL)
    new_funct->id = FUNC;
  else
    new_funct->id = FUNCNAMED;

  new_funct->func.token =  token;
  new_funct->func.args = args;
  new_funct->func.body = body;

  //sprintf(tmp_log,"init_funct token:%p, args->tok:%p, body:%p", token, args->tok, body);
  //mlog(tmp_log,2,0);

  return new_funct;
}

struct node_s * init_ternary(struct node_s * condition,struct node_s * thn,struct node_s * els){
  struct node_s * new_ternary = (struct node_s *)malloc(sizeof(struct node_s));
  new_ternary->id = TERNARY;
  new_ternary->ternary.condition =  condition;
  new_ternary->ternary.thn = thn;
  new_ternary->ternary.els = els;
  return new_ternary;
}

struct node_s * init_var2(struct token_s * token,struct node_s * exp){
  struct node_s * new_var = (struct node_s *)malloc(sizeof(struct node_s));
  new_var->id = VAR2;
  new_var->var2.token =  token;
  new_var->var2.exp = exp;
  return new_var;
}

struct node_s * init_var1(struct token_s * token){
  struct node_s * new_var = (struct node_s *)malloc(sizeof(struct node_s));
  new_var->id = VAR1;
  new_var->var1.token =  token;
  return new_var;
}

struct node_s * init_return1(){
  struct node_s * new_return = (struct node_s *)malloc(sizeof(struct node_s));
  new_return->id = RETURN1;
  new_return->ret.exp =  NULL;
  return new_return;
}

struct node_s * init_return2(struct node_s * exp){
  struct node_s * new_return = (struct node_s *)malloc(sizeof(struct node_s));
  new_return->id = RETURN2;
  new_return->ret.exp =  exp;
  return new_return;
}

struct node_s * init_ifthenelse(struct node_s * exp,struct list_node_s * thn,struct list_node_s * els){
  struct node_s * new_ifthenelse = (struct node_s *)malloc(sizeof(struct node_s));
  new_ifthenelse->id = IFTHENELSE;
  new_ifthenelse->ifthenelse.exp =  exp;
  new_ifthenelse->ifthenelse.thn =  thn;
  new_ifthenelse->ifthenelse.els =  els;
  return new_ifthenelse;
}

struct node_s * init_while(struct node_s * condition,struct list_node_s * body){
  struct node_s * new_while = (struct node_s *)malloc(sizeof(struct node_s));
  new_while->id = WHILE;
  new_while->whil.condition =  condition;
  new_while->whil.body = body;
  return new_while;
}

struct node_s* init_branch(struct token_s* tok) {

  struct node_s * new_branch = (struct node_s *)malloc(sizeof(struct node_s));

  new_branch->id = BRANCH;
  new_branch->branch.tok = tok;

  return new_branch;
}
