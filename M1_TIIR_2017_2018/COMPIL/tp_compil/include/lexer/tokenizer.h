#ifndef TOKENIZER_H
#define TOKENIZER_H

#include "token.h"

extern int curr_line, curr_column;

void skip_blanks();

struct token_s *is_a_sign();
struct token_s *is_a_keyword();
struct token_s *is_a_valued_token();

struct token_s * lex();

#endif
