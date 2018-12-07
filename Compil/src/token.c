#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "token.h"
#include "interprete/unserializer.h"

void print_token_s(struct token_s* tok) {

  printf("token: id = %d, line = %d, column = %d, length = %d\n", tok->id, tok->line, tok->column, tok->length);
  printf("value = %s\n", tok->value);
}


struct token_s* read_token() {

  struct token_s* tok = malloc(sizeof(struct token_s));
  assert(tok != NULL);

  tok->id     = read_byte();
  tok->line   = read_word16();
  tok->column = read_word16();
  tok->length = read_word16();
  tok->value  = malloc(sizeof(unsigned char) * tok->length);
  assert(tok->value != NULL);

  for (int i =0; i< tok->length; i++) {
    tok->value[i] = read_byte();
  }

  return tok;
}

struct list_token_s* add_token_to_list(struct list_token_s* tok_list, struct token_s* tok) {

  struct list_token_s* tmp = tok_list;
  struct list_token_s* new = malloc(sizeof(struct list_token_s));

  assert(new != NULL);
  new->next = NULL;
  new->tok = tok;

  if (tok_list->tok == NULL) {
    tok_list->tok = tok;
    free(new);
  }
  else {
    while(tmp->next != NULL) {
      tmp = tmp->next;
    }

    tmp->next = new;
  }

  return tok_list;
}

void display_tok_list( struct list_token_s* list) {

  struct list_token_s* it = list;

  printf(" === display_tok_list ===\n");
  while (it != NULL) {
    print_token_s(it->tok);
    it = it->next;
  }
  printf(" ======\n");

}

struct list_token_s* read_token_list() {

  unsigned int len = read_word32();
  struct token_s* tok;
  struct list_token_s* tok_list = malloc(sizeof(struct list_token_s));

  //sprintf(tmp_log, "read_token_list() .... len = %d", len);
  //mlog(tmp_log, 2 ,0);

  assert(tok_list != NULL);

  tok_list->next = NULL;

  while (len-- > 0) {
    tok = read_token();
    tok_list = add_token_to_list(tok_list, tok);
  }

  return tok_list;
}