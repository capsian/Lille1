#include <stdio.h>

#include "rules.h"

struct tree_s* parse_add() {
    return expression();
}

struct tree_s* parse_mul() {
    return terme();
}

// struct tree_s* parse_add_mul() {
//
//   struct tree_s* root = NULL;
//   struct tree_s* tmp = NULL;
//
//   do {
//
//     tmp = expression();
//
//     /* tmp == LIT */
//     if (tmp->token.)
//
//   }
//   while (tmp != NULL)
//
// }
