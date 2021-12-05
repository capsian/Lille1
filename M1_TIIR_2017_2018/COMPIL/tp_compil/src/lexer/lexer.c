#include <stdio.h>
#include <string.h>
#include <getopt.h>

#include "lexer/lexer.h"
#include "lexer/tokenizer.h"
#include "utils.h"

FILE *fd_in, *fd_out;

void lexer(char* input, char* output) {

    mlog("lexer() enter ....",2,0);

    struct token_s *token = NULL;

    fd_in  = fopen(input,"r");;
    fd_out = fopen(output,"w");

    /* fail */
    if (!fd_in || !fd_out)
        mlog("lexer() fd_in, fd_out fails !!!\n",0,1);

    while (1) {

        skip_blanks();
        token = lex();

        /* FINISH || FAIL */
        if (token == NULL) {
            break;
        }

        dump_token(token,fd_out);
        print_token(*token);
    }

    fclose(fd_in);
    fclose(fd_out);

    mlog("lexer() exit ....",2,0);
    return;
}

void usage() {

    mlog("usage...",0,0);
    mlog(" lexer -i <input_file>",0,0);
    mlog(" lexer -i <input_file> -o <output_file>",0,1);
}

int main(int argc, char** argv) {

    //set_verbose(1);

    int c = 0;
    char in_file[255] = {'0'}, out_file[255] = {'0'};

    while ((c = getopt (argc, argv, "io:")) != -1) {

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
        mlog("Error while parsing args !!!",0,0);
        usage();
    }

    /* check output */
    if (out_file[0] == '0') {
        strcpy(out_file, in_file);
        strcat(out_file, ".lex");
    }

    lexer(in_file, out_file);

    return 0;
}
