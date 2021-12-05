#ifndef TREE_H
#define TREE_H

#include "lexer/unlex_tokens.h"

struct tree_s {

    unsigned int index;

    struct tokenizer_s token;

    struct tree_s* right;
    struct tree_s* left;
};

struct fifo_s {

    struct tree_s* tree;
    struct fifo_s* next;
};

extern struct fifo_s* FIFO;

struct tree_s* init_tree();
struct tree_s* init_node (struct tree_s* node, struct tokenizer_s ntoken);
struct tree_s* add_right(struct tree_s* root, struct tree_s* son);
struct tree_s* add_left(struct tree_s* root, struct tree_s* son);
struct tree_s* add_root_right(struct tree_s* old_root, struct tree_s* new_root);
struct tree_s* add_root_left(struct tree_s* old_root, struct tree_s* new_root);

void add_fifo(struct tree_s* node);
struct tree_s* get_fifo();
void print_tree_BFS(struct tree_s* root,ulong prof);

#endif
