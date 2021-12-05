#ifndef TOKEN_H
#define TOKEN_H

#define STR_MAX_SIZE 255
#define FLT_MAX_SIZE 255
#define IDTNFR_MAX_SIZE 255

struct token_s {
    unsigned char id;
    unsigned int line;
    unsigned int column;
    unsigned int length;
    union {
        char c;
        char str[STR_MAX_SIZE];
        int number;
        char flt[FLT_MAX_SIZE];
        char idntfr[IDTNFR_MAX_SIZE];
    };
};

struct unlexed_token_s {
    unsigned char id;
    unsigned short line;
    unsigned short column;
    unsigned short length;
    char* value;
};

int isSign(int tokenId);
int isKeyword(int tokenId);

void dump_token(struct token_s * token,FILE * fd_out);
void print_token(struct token_s token);

#endif
