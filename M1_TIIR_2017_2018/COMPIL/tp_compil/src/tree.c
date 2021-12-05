#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "token.h"
#include "tree.h"

struct fifo_s* FIFO;

void add_fifo(struct tree_s* node) {

    struct fifo_s* new_elem = malloc(sizeof(struct fifo_s));
    new_elem->tree = node;
    new_elem->next = NULL;
    if (FIFO == NULL) {
        FIFO = new_elem;
    }
    else {
      //Ajout en queue
        struct fifo_s * tmp = FIFO;
        while(tmp->next != NULL)
          tmp = tmp->next;
        tmp->next = new_elem;
    }

}

struct tree_s* get_fifo() {

    struct tree_s* tmp_tree;
    struct fifo_s* tmp = FIFO;

    if (FIFO == NULL)
        return NULL;

    FIFO = FIFO->next;
    tmp_tree = tmp->tree;
    free(tmp);

    return tmp_tree;
}


struct tree_s* init_tree() {

    struct tree_s * root = malloc(sizeof(struct tree_s));

    root->index = 0;

    /* init the token */

    root->token.id         = 0;

    root->token.line       = 0;
    root->token.column     = 0;
    root->token.nb_octets  = 0;
    memset(root->token.value.string,'\0',32);

    root->left   = NULL;
    root->right  = NULL;

    return root;
}

struct tree_s* init_node (struct tree_s* node, struct tokenizer_s ntoken) {

    node->left = NULL;
    node->right = NULL;

    node->index = ntoken.id;
    node->token = ntoken;

    return node;
}

struct tree_s* add_right(struct tree_s* root, struct tree_s* son) {

    /* right son already exist */
    if (root->right != NULL) {
        printf("Error while adding right son\n");
        exit(EXIT_FAILURE);
    }
    /* right son NULL */
    if (son == NULL) {
        printf("Error while adding right son == NULL\n");
        return root;
    }

    root->right = son;

    return root;
}

struct tree_s* add_left(struct tree_s* root, struct tree_s* son) {

    /* left son already exist */
    if (root->left != NULL) {
        printf("Error while adding left son\n");
        exit(EXIT_FAILURE);
    }
    /* left son NULL */
    if (son == NULL) {
        printf("Error while adding left son == NULL\n");
        return root;
    }

    root->left = son;

    return root;
}

struct tree_s* add_root_right(struct tree_s* old_root, struct tree_s* new_root) {

    /* new_root NULL */
    if (new_root == NULL) {
        printf("Error while adding new_root == NULL\n");
        return old_root;
    }
    /* right son already exist */
    assert(new_root->right == NULL);

    new_root->right = old_root;

    return new_root;
}

struct tree_s* add_root_left(struct tree_s* old_root, struct tree_s* new_root) {

    /* new_root NULL */
    if (new_root == NULL) {
        printf("Error while adding new_root == NULL\n");
        return old_root;
    }
    /* left son already exist */
    assert(new_root->left == NULL);

    new_root->left = old_root;

    return new_root;
}



void print_tree_BFS(struct tree_s* root, ulong prof)
{
    ulong i;
    for (i=0; i < prof; i++)
    {
        fputs("|___ ", stdout);
    }

    printf("[%d] (%s)\n", root->token.id,root->token.value.string);
    if (root->left) print_tree_BFS(root->left, prof + 1);
    if (root->right) print_tree_BFS (root->right, prof + 1);
}

