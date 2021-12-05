/* ------------------------------
   $Id: if_dfile.c,v 1.1 2009/11/16 05:38:07 marquet Exp $
   ------------------------------------------------------------

   Delete a given file identified by its inumber
   Philippe Marquet, Nov 2009
   
*/

#include <stdio.h>
#include <stdlib.h>
#include "../../include/5/ifile.h"
#include "../../include/3/bloc.h"
#include "../../include/utils.h"

static void dfile(unsigned int inumber) {
    int status;
    
    status = delete_ifile(inumber);
    if(!status) {
        printf("ERROR dfile(), inumber = %d\n", inumber);
        exit(EXIT_FAILURE);
    }

    
}

static void usage(const char *prgm) {
    fprintf(stderr, "[%s] usage:\n\t"
            "<vol> %s inumber\n", prgm, prgm);
    exit(EXIT_FAILURE);
}

int main (int argc, char *argv[]) {
 
	unsigned int inumber;
	
    if (argc != 3)
        usage(argv[0]);
	
	current_vol = strtol(argv[1], NULL, 10);
    inumber = strtol(argv[2], NULL, 10);
    /*set_verbose (1);*/

    mount(current_vol);
    dfile(inumber);
    umount();
    
    exit(EXIT_SUCCESS);         
}
