#include <stdio.h>
#include <stdlib.h>

#include "../../include/utils.h"
#include "../../include/3/bloc.h"
#include "../../include/4/inode.h"
#include "../../include/5/ifile.h"


static void cfile(unsigned int sinumber) {

    file_desc_t sfd, dfd;
    unsigned int dinumber;
    int status;
    int c;
    
    dinumber = create_ifile(file);
    if (!dinumber) {

        printf("erreur creation fichier, dinumber = %d\n", dinumber);
        exit(EXIT_FAILURE);
    }
    printf(" creation fichier, dinumber = %d\n", dinumber);

    status = open_ifile(&dfd, dinumber);
    if (!status) {

        printf("erreur ouverture fichier, dinumber = %d\n", dinumber);
        exit(EXIT_FAILURE);
    }
    printf(" ouverture fichier, dinumber = %d\n", dinumber);


    status = open_ifile(&sfd, sinumber);
    if (!status) {

        printf("erreur ouverture fichier, sinumber = %d\n", sinumber);
        exit(EXIT_FAILURE);
    }
    printf(" ouverture fichier, sinumber = %d\n", sinumber);


    while((c=readc_ifile(&sfd)) != FILE_EOF)
        writec_ifile(&dfd, c);

    close_ifile(&dfd);
    close_ifile(&sfd);
}

static void usage(const char *prgm) {

    fprintf(stderr, "[%s] usage:\n\t" "%s <vol> <inumber>\n", prgm, prgm);
    exit(EXIT_FAILURE);
}

int main (int argc, char *argv[]) {

    unsigned inumber;

    if (argc < 3)
        usage(argv[0]);

    current_vol = strtol(argv[1], NULL, 10);
	inumber = strtol(argv[2], NULL, 10);
	
    mount(current_vol);

    cfile(inumber);

    umount();
    
    exit(EXIT_SUCCESS);         
}