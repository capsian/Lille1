#include <stdlib.h>
#include <stdio.h>
#include "lexer/symbol.h"
#include "token.h"
#include "lexer/unlex_tokens.h"
#include "tree.h"



struct tree_s* facteur() {

    struct tree_s* res = (struct tree_s *)malloc(sizeof(struct tree_s));
    struct tokenizer_s token;

    token = get_token();

    /* check if NUMBER */
    switch (token.id) {

        case IDENTIFIER:
        case INTEGER:
        case FLOAT:
            init_node(res, token);
            next_token();
            break;

        /* FAIL */
        default:

            free(res);
            res = NULL;
            break;
    }

    return res;
}

struct tree_s* terme() {

    struct tree_s* last_node = NULL;
    struct tree_s * tmp_tree = NULL;
    struct tree_s * pivot_node = NULL;

    struct tokenizer_s curr_token;

    /* get first elem && next_token() && init */
    last_node = facteur();

    /* FAIL */
    if (last_node == NULL) {
        return NULL;
    }

    /* read MUL */
    curr_token = get_token();

    /* get all the MUL && DIV */
    while ( (curr_token.id == ASTERISK) || (curr_token.id == SLASH)) {

      /* ADD the operator node */
      struct tree_s* operator_node = init_tree();
      init_node(operator_node, curr_token);

      /* next && read LIT */
      next_token();
      pivot_node = facteur();

      /* init the last node of the tree ||   Lit - OP - Lit */
      if (tmp_tree == NULL) {
        add_left(operator_node,last_node);

        /* add to the root */
        add_right(operator_node, pivot_node);
      }
      /*
        * check if we already have a tree
        * connect the 2 trees
      */
      else {

        /* add the pivot */
        add_right(operator_node, pivot_node);

        /* attach */
        add_root_left(tmp_tree, operator_node);
      }

      curr_token = get_token();

      tmp_tree = operator_node;
    }


    /* we caught a valid MUL sequence */
    if(tmp_tree != NULL){
        return tmp_tree;
    }

    /* we just caught a number */
    return last_node;
}


struct tree_s* expression() {

  struct tree_s* last_node = NULL;
  struct tree_s * tmp_tree = NULL;
  struct tree_s * pivot_node = NULL;

  struct tokenizer_s curr_token;

  /* get first elem && next_token() && init */
  last_node = terme();

  /* FAIL */
  if (last_node == NULL) {
      return NULL;
  }

  /* read MUL */
  curr_token = get_token();

  /* get all the MUL && DIV */
  while ( (curr_token.id == PLUS) || (curr_token.id == MINUS)) {

    /* ADD the operator node */
    struct tree_s* operator_node = init_tree();
    init_node(operator_node, curr_token);

    /* next && read LIT */
    next_token();
    pivot_node = terme();

    /* init the last node of the tree ||   Lit - OP - Lit */
    if (tmp_tree == NULL) {
      add_left(operator_node,last_node);

      /* add to the root */
      add_right(operator_node, pivot_node);
    }
    /*
      * check if we already have a tree
      * connect the 2 trees
    */
    else {

      /* add the pivot */
      add_right(operator_node, pivot_node);

      /* attach */
      add_root_left(tmp_tree, operator_node);
    }

    curr_token = get_token();

    tmp_tree = operator_node;
  }

  /* FAIL, return LIT || ADD_EXP */
  if(tmp_tree == NULL){
    return last_node;
  }

  /* we just caught an EXP OR NOTHING */
  return tmp_tree;
}
