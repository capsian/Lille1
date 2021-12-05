#include <stdio.h>
#include <stdlib.h>

#include "../../include/utils.h"
#include "../../include/3/bloc.h"
#include "../../include/4/inode.h"
#include "../../include/5/ifile.h"

static void pfile(unsigned int inumber) {
    
    file_desc_t fd;
    int status;
    int c;
    
    if (verbose)
        printf("pfile() enter ... with inumber = %d\n",inumber);
    
    status = open_ifile(&fd, inumber);

	if (!status) {
		
		printf("erreur ouverture fichier %d\n", inumber);
		exit(EXIT_FAILURE);
	}

    while((c=readc_ifile(&fd)) != FILE_EOF) {
	    putchar(c);
    }

    printf("\n");
    close_ifile(&fd);
    
    if (verbose)
        printf("pfile() exit ...\n");
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

	pfile(inumber);

    umount();
    
    exit(EXIT_SUCCESS);         
}
