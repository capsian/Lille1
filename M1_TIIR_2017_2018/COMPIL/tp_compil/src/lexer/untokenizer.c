#include "lexer/untokenizer.h"
#include <stdlib.h>
#include <stdio.h>
#include "token.h"
#include "lexer/unlex_tokens.h"
struct liste_tokenizer_s * all_tokens = NULL;

void add_element(struct tokenizer_s new_token){
    struct liste_tokenizer_s * new_elem = (struct liste_tokenizer_s *) malloc(sizeof(struct liste_tokenizer_s));
    if(new_elem == NULL){
        fprintf(stderr, "%s\n","Unable to add the new element" );
        exit(EXIT_FAILURE);
    }
    new_elem->value = new_token;
    //Lal iste est vide
    if(all_tokens == NULL){
        new_elem->next = NULL;
        new_elem->previous = NULL;
        all_tokens = new_elem;
    }else{
        //On l'ajoute en queue
        struct liste_tokenizer_s * tmp = all_tokens;
        //On arrive en fin de liste
        while(tmp->next != NULL){
            tmp = tmp->next;
        }
        //Ajout du nouvel élément
        new_elem->previous = tmp;
        new_elem->next = NULL;
        tmp->next = new_elem;
    }
}

void unlex_tokens(char * lex_file){
    //Start to open the FILE
    FILE * lexed_file;
    struct tokenizer_s new_token;
    char c = 0;
    int i;
    unsigned char id;
    short line,column,nb_octets;
    lexed_file = fopen(lex_file,"rb");
    //Le fichier n'est pas accessible
    if(lexed_file == NULL){
        fprintf(stderr, "%s\n","Unable to open the lexed file" );
        fclose(lexed_file);
        exit(EXIT_FAILURE);
    }
    c = fgetc(lexed_file);
    while (c != EOF) {
        //Start to read all tokens

        //The first octect should be an id
        id = (unsigned char)c;
        //The next two octet are the line
        c = fgetc(lexed_file);
        line = (unsigned char)c;
        line <<= 8;
        c = fgetc(lexed_file);
        line += (unsigned char)c;
        //The next two octet are the column
        c = fgetc(lexed_file);
        column = (unsigned char)c;
        column <<= 8;
        c = fgetc(lexed_file);
        column += (unsigned char)c;
        //The next two octet are the number of octet for a valued token
        c = fgetc(lexed_file);
        nb_octets = (unsigned char)c;
        nb_octets <<= 8;
        c = fgetc(lexed_file);
        nb_octets += (unsigned char)c;
        //Add to the new_token
        new_token.id = id;
        new_token.line = line;
        new_token.column = column;
        new_token.nb_octets = nb_octets;
        //Read all octet for the value if necesserary
        for(i = 0; i < nb_octets;i++){
            c = fgetc(lexed_file);
            new_token.value.string[i] = (unsigned char)c;
        }
        new_token.value.string[i] = '\0';
        //Add the new token to the liste
        add_element(new_token);
        c = fgetc(lexed_file);
    }

    new_token.id = 255;
    new_token.column = 0;
    new_token.line = 0;
    new_token.nb_octets = 0;
    add_element(new_token);

    fclose(lexed_file);
}

void next_token(){
    if(all_tokens->next != NULL)
        all_tokens = all_tokens->next;
}
void previous_token(){
    if(all_tokens->previous != NULL)
        all_tokens = all_tokens->previous;
}

struct tokenizer_s get_token(){
    return all_tokens->value;
}