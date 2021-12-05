#include <stdio.h>

#include "lexer/symbol.h"
#include "token.h"
#include "utils.h"

void putword16(int word16, FILE *fd_out) {
    putc((word16 >> 8) & 255, fd_out);
    putc(word16 & 255, fd_out);
}

void putword32(int word32, FILE *fd_out) {
    putword16((word32 >> 16) & 0xFFFF, fd_out);
    putword16(word32 & 0xFFFF, fd_out);
}

int isSign(int tokenId) {
    return tokenId > SIGNS && tokenId <= SIGNS + NB_SIGNS && signs[tokenId] != NULL;
}

int isKeyword(int tokenId) {
    return tokenId > KEYWORDS && tokenId <= KEYWORDS + NB_KEYWORDS;
}

void dump_token(struct token_s *token, FILE *fd_out) {

    putc(token->id, fd_out);
    putword16(token->line, fd_out);
    putword16(token->column, fd_out);
    putword16(token->length, fd_out);

    if (isSign(token->id)) {
        fprintf(fd_out, "%s", signs[token->id & ~SIGNS]);
    } else if (isKeyword(token->id)) {
        fprintf(fd_out, "%s", keywords[token->id & ~KEYWORDS]);
    } else {
        switch (token->id) {

            case FLOAT :
                for(unsigned int i=0;i<token->length;i++)
                    putc(token->flt[i], fd_out);
                break;

            case INTEGER:
                putc(token->number, fd_out);
                break;

            case CHAR:
                putc(token->c, fd_out);
                break;

            case STRING :
                for (unsigned int i = 0; i < token->length; i++)
                    putc(token->str[i], fd_out);
                break;

            case IDENTIFIER :
                for (unsigned int i = 0; i < token->length; i++)
                    putc(token->idntfr[i], fd_out);
                break;

            default:
                set_verbose(1);
                printf("tokenId = %d\n", token->id);
                mlog("dump_token(), unkown tokenID !!!", 0, 1);
                break;
        }
    }
}

void print_token(struct token_s token) {

    printf("--- print_token ---\n");
    printf("tokenId: %d\n", token.id);
    printf("line: %d, column: %d, length:%d\n", token.line, token.column, token.length);
    printf("value : ");
    if (isSign(token.id)) {
        printf(" (sign) (index:%d)\n", token.id & ~SIGNS);
        printf("%s\n",signs[token.id & ~SIGNS]);
    }
    else if (isKeyword(token.id)) {
        printf(" (keyword)\n");
        printf(" (keyword) (index:%d)\n", token.id & ~KEYWORDS);
        printf("%s\n",keywords[token.id & ~KEYWORDS]);
    }
    else {
        switch (token.id) {
            case FLOAT :
                printf(" (FLOAT)\n");
                printf("%s\n",token.flt);
                break;
            case INTEGER:
                printf(" (INTEGER)\n");
                printf("%d\n",token.number);
                break;
            case CHAR:
                printf(" (CHAR)\n");
                printf("%c\n",token.c);
                break;
            case STRING :
                printf(" (STRING)\n");
                printf("%s\n",token.str);
                break;
            case IDENTIFIER :
                printf(" (IDENTIFIER)\n");
                printf("%s\n",token.idntfr);
                break;

            default:
                set_verbose(1);
                mlog("dump_token(), unkown tokenID !!!", 0, 1);
                break;
        }
    }

    printf("--------\n");
}
