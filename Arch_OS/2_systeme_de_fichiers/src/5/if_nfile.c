#include <stdio.h>
#include <stdlib.h>

#include "../../include/utils.h"
#include "../../include/2/vol.h"
#include "../../include/3/bloc.h"
#include "../../include/4/inode.h"
#include "../../include/5/ifile.h"

static void nfile() {
    
    file_desc_t fd;
    unsigned int inumber;
    int status;
    int c;
	
	if (verbose)
        printf("nfile() enter ...\n");
    
    inumber = create_ifile(file);
    if (!inumber) {

        printf("erreur creation fichier, inumber = %d\n", inumber);
        exit(EXIT_FAILURE);
    }
    printf(" created file ! inumber = %d\n",inumber);
    
    status = open_ifile(&fd, inumber);
    if (!status) {

        printf("erreur ouverture fichier %d\n", inumber);
        exit(EXIT_FAILURE);
    }
    printf(" opened file !\n");
    
    printf(" i write .... \n");
    while((c=getchar()) != FILE_EOF) {

       writec_ifile(&fd, c);
    }
    printf(" DONE !!\n ");
    
    close_ifile(&fd);
	
    if (verbose)
        printf("nfile() exit ...\n");
}

static void usage(const char *prgm) {
    
    fprintf(stderr, "[%s] usage:\n\t" "%s <vol>\n", prgm, prgm);
    exit(EXIT_FAILURE);
}

int main (int argc, char *argv[]) {
	
	if (argc < 1) {
	    usage(argv[0]);
    }
	
	current_vol = strtol(argv[1], NULL, 10);
	/*set_verbose (1);*/
	
	mount(current_vol);

    nfile();
	
    umount();
    
    exit(EXIT_SUCCESS);         
}
