#ifndef TOKEN_H
#define TOKEN_H

struct token_s {
    unsigned char id;
    unsigned short line;
    unsigned short column;
    unsigned short length;
    char* value;
};

void print_token_s(struct token_s* tok);
struct list_token_s* read_token_list();
struct list_token_s* add_token_to_list(struct list_token_s* tok_list, struct token_s* tok);
struct token_s* read_token();

void display_tok_list( struct list_token_s* list);

#endif
