#ifndef UNSERIALIZER_H
#define UNSERIALIZER_H

#include "interprete/structs.h"

struct list_token_s {
    struct token_s* tok;
    struct list_token_s* next;
};


struct list_node_s* read_statement_list();
struct node_s* read_statement();
struct list_node_s* read_expression_list();
struct list_node_s* add_node_to_list(struct list_node_s* list, struct node_s* insert);
struct node_s* read_expression(int nodeId);
struct list_token_s* read_token_list();
struct list_token_s* add_token_to_list(struct list_token_s* tok_list, struct token_s* tok);
struct token_s* read_token();

#endif
