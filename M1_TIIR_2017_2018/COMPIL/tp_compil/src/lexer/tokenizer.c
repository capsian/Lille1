#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lexer/tokenizer.h"
#include "lexer/lexer.h"
#include "lexer/symbol.h"
#include "utils.h"

int curr_line = 1;
int curr_column = 1;

void skip_blanks() {

    char c;
    int stop1 = 0;
    int stop2 = 0;
    char tmp[255];

    sprintf(tmp,"skip_blanks() enter ... curr_line:%d, curr_col:%d",curr_line,curr_column);
    mlog(tmp,2,0);

    while (!(stop1) && c != EOF) {

        c = fgetc(fd_in);
        curr_column++;

        /* NEW LINE */
        if (c == '\n') {

            mlog(" new line catched !",2,0);

            curr_line++;
            curr_column = 1;
        }
            /* open comment */
        else if (c == '/') {

            c = fgetc(fd_in);
            curr_column++;

            /* multiline comment, eat until \*\/ */
            if (c == '*') {

                mlog(" multine comment catched !",2,0);

                while (!stop2 && c != EOF) {
                    c = fgetc(fd_in);
                    curr_column++;
                    if (c == '\n') {
                        curr_line++;
                        curr_column = 1;
                    }
                    if (c == '*') {

                        c = fgetc(fd_in);
                        curr_column++;

                        /* stop MULTILINE COMMENT */
                        if (c == '/') {

                            mlog(" multine comment stop !",2,0);

                            stop2 = 1;

                        } else {
                            fseek(fd_in, -1, SEEK_CUR);
                        }
                    }
                }
            }
                /* inline comment, eat until / */
            else if (c == '/') {

                mlog(" inline comment catched !",2,0);

                while (c != '\n' && c != EOF) {
                    c = fgetc(fd_in);
                }
                curr_column = 1;
                curr_line++;

            } else {  // valid input, return in the file and stop

                stop1 = 1;
                fseek(fd_in, -2, SEEK_CUR);
                curr_column -= 1;
            }
        }
        else if (c == ' ' || c == '\t') {
            mlog(" space | tab catched !",2,0);

        }
        else {    // DONE

            sprintf(tmp,"skip_blanks() Done !! ... curr_line:%d, curr_col:%d, c=%c",curr_line,curr_column,c);
            mlog(tmp,2,0);
            stop1 = 1;
            fseek(fd_in, -1, SEEK_CUR);
            curr_column--;
        }
    }

    sprintf(tmp,"skip_blanks() exit ... curr_line:%d, curr_col:%d",curr_line,curr_column);
    mlog(tmp,2,0);
}

struct token_s *is_a_sign() {

    char c[5];
    char tmp[255];
    int j, k;

    sprintf(tmp,"is_a_sign() enter ... curr_line:%d, curr_col:%d",curr_line,curr_column);
    mlog(tmp,2,0);

    for (j = 0; j < 4; j++) {

        c[j] = fgetc(fd_in);

        curr_column++;

        if (c[j] == EOF) {
            curr_column--;
            break;
        }
    }
    k = j;

    for (; j > 0; j--) {

        c[j] = '\0';

        for (int i = 0; i < NB_SIGNS; i++) {

            if (my_compare(c, signs[i]) == 0) {

                struct token_s *ntoken = (struct token_s *) malloc(sizeof(struct token_s));

                ntoken->id = i;
                ntoken->line = curr_line;
                ntoken->column = curr_column - j;
                ntoken->length = strlen(signs[i]);

                fseek(fd_in, -(k - j), SEEK_CUR);

                return ntoken;
            }
        }
        curr_column--;
    }

    // fail, back to init pos
    fseek(fd_in, -k, SEEK_CUR);
    return NULL;
}

struct token_s *is_a_keyword() {

    char c[11];
    char tmp;
    char tmp_log[255];
    int i, j, id_token, stop, k;

    sprintf(tmp_log,"is_a_keyword() enter ... curr_line:%d, curr_col:%d",curr_line,curr_column);
    mlog(tmp_log,2,0);

    id_token = 0;
    stop = 0;

    /* fill the buffer c with max keyword length */
    for (j = 0; j < 10; j++) {

        curr_column++;
        c[j] = fgetc(fd_in);

        if (c[j] == EOF) {
            curr_column--;
            break;
        }
    }
    k = j;

    /* try to catch a keyword */
    for (; j > 0; j--) {

        c[j] = '\0';

        for (i = 0; i < NB_KEYWORDS; i++) {
            if (my_compare(c, keywords[i]) == 0) {
                id_token = i;
                stop = 1;
                break;
            }
        }
        if (stop) {
            break;
        } else {
            curr_column--;
        }
    }

    /* FAIL, no keyword */
    if (j == 0) {

        fseek(fd_in, -k, SEEK_CUR);

        return NULL;
    }

    //On vérifie si derriere le keyword il n'y a pas une lettre ou un chiffre
    fseek(fd_in, -(10 - j), SEEK_CUR);
    tmp = fgetc(fd_in);
    fseek(fd_in, -1, SEEK_CUR);

    if ((tmp >= '0' && tmp <= '9') || (tmp >= 'A' && tmp <= 'Z') || (tmp >= 'a' && tmp <= 'z')) {
        fseek(fd_in, -j, SEEK_CUR);
        curr_column -= k - j;
        return NULL;
    }

    struct token_s *ntoken = (struct token_s *) malloc(sizeof(struct token_s));
    ntoken->id = 64 + id_token;

    ntoken->line = curr_line;
    ntoken->column = curr_column - j;
    ntoken->length = strlen(keywords[ntoken->id & ~KEYWORDS]);

    return ntoken;
}

struct token_s *is_a_valued_token() {

    char tmp_log[255];
    sprintf(tmp_log,"is_a_keyword() enter ... curr_line:%d, curr_col:%d",curr_line,curr_column);
    mlog(tmp_log,2,0);


    char c = fgetc(fd_in);
    struct token_s *ntoken = (struct token_s *) malloc(sizeof(struct token_s));


    /* STRING */
    if (c == '\"') {

        int i = 0;
        ntoken->id = STRING;

        while ((c = fgetc(fd_in)) != EOF && c != '\"') {
            if (i < 254)
                ntoken->str[i++] = c;
            curr_column++;
        }

        ntoken->str[i] = '\0';
        ntoken->length = i;
        ntoken->line = curr_line;
        ntoken->column = curr_column;

        /* SUCCESS */
        return ntoken;
    }
        /* FLOAT | INTEGER */
    else if (c >= '0' && c <= '9') {

        ntoken->line = curr_line;
        ntoken->column = curr_column;

        int i = 0;
        char tmp_buffer[FLT_MAX_SIZE];

        while (c != EOF && (c >= '0' && c <= '9')) {
            tmp_buffer[i++] = c;
            c = fgetc(fd_in);
            curr_column++;
        }

        /* FLOAT */
        if (c == '.') {

            tmp_buffer[i++] = c;

            c = fgetc(fd_in);
            curr_column++;

            // TODO LIRE LES NOMBRES PUIS LES REVERSE ET LES CONVERTIR EN CHIFFRE ET DIVISION PAR 10.
            while (c != EOF && (c >= '0' && c <= '9')) {
                tmp_buffer[i++] = c;
                c = fgetc(fd_in);
                curr_column++;
            }

            tmp_buffer[i] = '\0';
            ntoken->id = FLOAT;
            ntoken->length = i;
            fseek(fd_in, -1, SEEK_CUR);

            memcpy(ntoken->flt,tmp_buffer,FLT_MAX_SIZE);

            return ntoken;
        }
            /* INTEGER */
        else {

            fseek(fd_in, -1, SEEK_CUR);
            tmp_buffer[i] = '\0';
            ntoken->id = INTEGER;
            ntoken->length = i;

            ntoken->number = atoi(tmp_buffer);

            return ntoken;
        }
    }
        /* CHAR */
    else if (c == '\'') {

        ntoken->c = fgetc(fd_in);

        /* fail, fallback */
        if ((c = fgetc(fd_in)) != '\'') {
            fseek(fd_in, -3, SEEK_CUR);

            /* FAIL */
            return NULL;
        }

        ntoken->line = curr_line;
        ntoken->column = curr_column;
        ntoken->length = 1;
        ntoken->id = CHAR;
        curr_column += 3;

        /* SUCCESS */
        return ntoken;
    }
        /* IDENTIFIER */
    else if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {

        ntoken->id = IDENTIFIER;
        ntoken->column = curr_column;
        ntoken->line = curr_line;
        int i = 0;

        while ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9')) {
            curr_column++;
            if (i < 254)
                ntoken->idntfr[i++] = c;
            c = fgetc(fd_in);
        }
        ntoken->idntfr[i] = '\0';
        ntoken->length = i;
        curr_column--;
        fseek(fd_in, -1, SEEK_CUR);

        /* SUCCESS */
        return ntoken;
    }

    /* FAIL */
    if (ntoken)
        free(ntoken);

    return NULL;
}

struct token_s * lex() {

    struct token_s *token = NULL;

    /* SIGN */
    if ((token = is_a_sign()) != NULL) {
        mlog("lex() sign token catched ! ...",2,0);
        return token;
    }
        /* KEYWORD */
    else if ((token = is_a_keyword()) != NULL) {
        mlog("lex() keyword token catched ! ...",2,0);
        return token;
    }
        /* VAL TOKEN */
    else if ((token = is_a_valued_token()) != NULL) {
        mlog("lex() val token catched ! ...",2,0);
        return token;
    }
        /* FAIL */
    else {

        char c = fgetc(fd_in);
        /* STOP, SUCCESS ? */
        if (c == EOF)
            return 0;

        mlog("lex() failed !! ...",0,0);

        while (c != EOF) {
            putc(c, stdout);
            c = fgetc(fd_in);
        }

        return NULL;
    }
}