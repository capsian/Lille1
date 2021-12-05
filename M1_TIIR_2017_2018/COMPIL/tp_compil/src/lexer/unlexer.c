#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <getopt.h>

#include "lexer/symbol.h"
#include "token.h"
#include "utils.h"

FILE *infile;
FILE *outfile;

char getbyte() {
    char c;
    if (!feof(infile))
        c = fgetc(infile);
    else
        mlog("getbyte() ... unexpected eof !", 0, 1);
    return c;
}

int getword16() {
    int h, l;
    h = getbyte();
    l = getbyte();
    return (h << 8) | l;
}

int getword32() {
    int h = getword16();
    int l = getword16();
    return (h << 16) | l;
}

double getdouble() {
    double d;
    char *ptr = (char *) &d;
    for (int i = 0; i < 8; i++)
        *ptr++ = getbyte();
    return d;
}

void unlex(char *in, char *out) {

    struct token_s unlex_tok;
    int i,c;
    char tmp_log[255];
    char tmp_int[255];

    memset(tmp_log, '\0', 255);
    memset(tmp_int, '\0', 255);

    infile = fopen(in, "r");
    outfile = fopen(out, "w");

    sprintf(tmp_log,"unlex() enter ... in:%s, out:%s\n",in,out);
    mlog(tmp_log,2,0);

    while ((unlex_tok.id = fgetc(infile)) != -1) {

        unlex_tok.line = getword16();
        unlex_tok.column = getword16();
        unlex_tok.length = getword16();

        sprintf(tmp_log,"unlex() while ... tokId:%d, line:%d, col:%d, ln:%d\n",unlex_tok.id, unlex_tok.line, unlex_tok.column, unlex_tok.length);
        mlog(tmp_log,2,0);

        if ((isSign(unlex_tok.id )) || (isKeyword(unlex_tok.id))) {

            sprintf(tmp_log,"sign || keyword !! ln:%d\n",unlex_tok.length);
            mlog(tmp_log,2,0);

            fseek(infile, unlex_tok.length, SEEK_CUR);

        } else {
            switch (unlex_tok.id) {
                case STRING:

                    if (unlex_tok.length >= STR_MAX_SIZE)
                        mlog("unlex()... length >= STR_MAX_SIZE !!!", 0, 1);

                    fputc('\"', outfile);
                    for (i = 0; i < unlex_tok.length; i++) {
                        if (feof(infile))
                            mlog("unlex()... STRING: unexpected eof !!!", 0, 1);

                        c = fgetc(infile);
                        unlex_tok.str[i] = c;
                        fputc(c, outfile);
                    }
                    fputc('\"', outfile);
                    break;
                case IDENTIFIER:

                    if (unlex_tok.length >= IDTNFR_MAX_SIZE)
                        mlog("unlex()... length >= IDTNFR_MAX_SIZE !!!", 0, 1);

                    for (i = 0; i < unlex_tok.length; i++) {
                        if (feof(infile))
                            mlog("unlex()... IDENTIFIER: unexpected eof !!!", 0, 1);

                        c = fgetc(infile);
                        unlex_tok.idntfr[i] = c;
                        fputc(c, outfile);
                    }

                    break;
                case CHAR:
                    if (unlex_tok.length != 1)
                        mlog("unlex()... bad length for CHAR token !!", 0, 1);

                    c = getbyte();
                    unlex_tok.c = c;
                    fputc(c, outfile);
                    break;
                case INTEGER:
                    /*if (unlex_tok.length != 4)
                        mlog("unlex()... bad length for INTEGER token !!", 0, 1);*/

                    for (i = 1; i < unlex_tok.length; i++) {
                        if (feof(infile))
                            mlog("unlex()... INTEGER: unexpected eof !!!", 0, 1);

                        c = fgetc(infile);
                        tmp_int[i] = c;
                    }

                    printf("INT:(string)%s\n",tmp_int);
                    unlex_tok.number = atoi(tmp_int);
                    printf("INT:(int)%d\n",unlex_tok.number);
                    fprintf(outfile, "%d", unlex_tok.number);
                    memset(tmp_int, '\0', 255);
                    break;
                case FLOAT:
                    if (unlex_tok.length >= FLT_MAX_SIZE)
                        mlog("unlex()... length >= FLT_MAX_SIZE !!!", 0, 1);

                    for (i = 0; i < unlex_tok.length; i++) {
                        if (feof(infile))
                            mlog("unlex()... FLOAT: unexpected eof !!!", 0, 1);

                        c = fgetc(infile);
                        unlex_tok.flt[i] = c;
                        fputc(c, outfile);
                    }

                    break;
                default:
                    snprintf(tmp_log, "unlex()... bad token id:%d", unlex_tok.id);
                    if (((unlex_tok.id & SIGNS) == SIGNS && (unlex_tok.id & ~SIGNS) > NB_SIGNS) ||
                        ((unlex_tok.id & KEYWORDS) == KEYWORDS && (unlex_tok.id & ~KEYWORDS) > NB_KEYWORDS))

                        mlog(tmp_log, 0, 1);

                    break;
            }
        }

        print_token(unlex_tok);
    }

    fclose(infile);
    fclose(outfile);
}

void usage() {

    set_verbose(1);
    mlog("usage...", 0, 0);
    mlog(" unlexer -i <input_file>", 0, 0);
    mlog(" unlexer -i <input_file> -o <output_file>", 0, 1);
}

int main(int argc, char **argv) {

    set_verbose(1);

    int c = 0;
    char in_file[255] = {'0'}, out_file[255] = {'0'};

    while ((c = getopt(argc, argv, "io:")) != -1) {

        switch (c) {
            case 'i': {

                if (argv[optind] != NULL)
                    strcpy(in_file, argv[optind]);

                break;
            }
            case 'o': {

                if (argv[optind] != NULL)
                    strcpy(out_file, argv[optind]);

                break;
            }
            case '?':
            default:
                usage();
        }
    }

    /* FAILS */
    if (in_file[0] == '0') {
        mlog("Error while parsing args !!!", 0, 0);
        usage();
    }

    /* check output */
    if (out_file[0] == '0') {
        strcpy(out_file, in_file);
        strcat(out_file, ".unlex");
    }

    printf("CHECK !! out:%s, in:%s\n",out_file, in_file);
    unlex(in_file, out_file);

    return 0;
}
