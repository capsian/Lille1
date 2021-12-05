#ifndef UNTOKENIZER_H
#define UNTOKENIZER_H

#include "token.h"

struct liste_tokenizer_s {
    struct tokenizer_s value;
    struct liste_tokenizer_s * previous;
    struct liste_tokenizer_s * next;
};

void next_token();
void previous_token();
struct tokenizer_s get_token();
void unlex_tokens(char * lex_file);
void free_liste();

#endif
