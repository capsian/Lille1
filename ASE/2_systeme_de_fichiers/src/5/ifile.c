#include <stdio.h>
#include <string.h>

#include "../../include/5/ifile.h"
#include "../../include/4/inode.h"
#include "../../include/3/bloc.h"
#include "../../include/2/vol.h"
#include "../../include/utils.h"


/*------------------------------
  Create and delete file
  ------------------------------------------------------------*/

unsigned int create_ifile(enum file_type_e type) {

    unsigned int inumber;
	
	if (verbose)
		printf(" create_ifile() enter... with type= %d\n",type);

    inumber = create_inode(type);
	
	if (verbose)
		printf(" create_ifile() exit... with inumber= %d\n", inumber);
	
    return inumber;
}

int delete_ifile(unsigned int inumber) {
	
    delete_inode(inumber);

    return 1;
}


/*------------------------------
  Open, close and flush file
  ------------------------------------------------------------*/

int open_ifile(file_desc_t *fd, unsigned int inumber) {
    
    unsigned int first_bloc;
    struct inode_s inode;
    /* we are opening the designed file! */
    fd->inumber = inumber;
    read_inode (inumber, &inode);
    
    /* other trivial init */
    fd->size = inode.size;
    fd->pos = 0;
    
    /* the buffer is full of zeros if the first bloc is zero, loaded
       with this first bloc otherwise */
    first_bloc = vbloc_of_fbloc(inumber, 0, FALSE);
    if (! first_bloc)
        memset(fd->buf, 0, HDA_SECTORSIZE);
    else
        read_bloc(current_vol, first_bloc, fd->buf);
    
    /* last trivial */
    fd->dirty = FALSE;
    
    return 1;
}

void close_ifile(file_desc_t* fd) {

    flush_ifile(fd);
}

void flush_ifile(file_desc_t *fd) {

    int fbloc, vbloc;
    struct inode_s inode;

    if (fd->dirty) {

        fbloc = fd->pos / HDA_SECTORSIZE;
        vbloc = vbloc_of_fbloc(fd->inumber, fbloc, TRUE);

        read_inode(fd->inumber, &inode);
        if (fd->size > inode.size) {
            inode.size = fd->size;
            write_inode(fd->inumber, &inode);
        }

        write_bloc(current_vol, vbloc, fd->buf);
        fd->dirty = 0;
    }
}

/*------------------------------
  Seek in a file
  ------------------------------------------------------------*/

/* move the cursor of offset positions. */
void seek_ifile(file_desc_t *fd, int offset) {

    unsigned int old_pos = fd->pos;
    unsigned int fbloc, vbloc;

    /* update the position */
    fd->pos += offset;

    /* does the seek imply a jump in another bloc? */
    if ( (fd->pos / HDA_SECTORSIZE) != (old_pos / HDA_SECTORSIZE)) {
        /* flush */
        flush_ifile(fd);

        /* the bloc index of the new buffer */
        fbloc = fd->pos / HDA_SECTORSIZE;
        vbloc = vbloc_of_fbloc(fd->inumber, fbloc, FALSE);

        if (! vbloc)
            /* the bloc #0 is full of zeros */
            memset(fd->buf, 0, /*BLOC_SIZE*/HDA_SECTORSIZE);
        else
            /* load the bloc */
            read_bloc(current_vol, vbloc, fd->buf);
    }
}

/* move the cursor at offset */
void seek2_ifile(file_desc_t *fd, int offset) {

    seek_ifile(fd, offset - fd->pos);
}


/*------------------------------
  Read & Write a char in a file
  ------------------------------------------------------------*/

int readc_ifile(file_desc_t *fd) {

    int res;

    if (fd->pos >= fd->size) {
        if (verbose)
            printf(" readc_ifile(): FILE_EOF, fd->inumber = %d\n",fd->inumber);
        return FILE_EOF;
    }

    res = fd->buf[ fd->pos % HDA_SECTORSIZE];
    seek_ifile(fd, 1); /* seek_ifile(fd, pos+1) */

    return res;
}

/* return the  pos in the file ; RETURN_FAILURE in case of error */
int writec_ifile(file_desc_t *fd, unsigned char c) {

    unsigned int ibloc;
	
	if (verbose)
		printf(" writec_ifile() enter... with fd->inumber= %d\n",fd->inumber);

    /* write the char in the buffer */
    fd->buf[fd->pos % HDA_SECTORSIZE] = c;

    /* first write in the bloc ? ensure the data bloc allocation */
    if (! fd->dirty) {
        ibloc = vbloc_of_fbloc(fd->inumber, fd->pos / HDA_SECTORSIZE, TRUE);
	
	    if (verbose)
	        printf("! fd->dirty !!\n");
		    
        if (! ibloc) {
    
            if (verbose)
                printf("  [ERROR] writec_ifile(): vbloc_of_fbloc(%d, %d, TRUE), ibloc = %d\n", fd->inumber, ibloc, fd->pos / HDA_SECTORSIZE);
    
            return -1;
        }
        
        fd->dirty = TRUE;
    }

    /* is the buffer full? */
    if (fd->pos % HDA_SECTORSIZE == /*BLOC_SIZE*/HDA_SECTORSIZE-1) {
	
	   /* if (verbose)
		    printf("  writec_ifile(): buffer full\n");
	    
        *//* write the buffer*//*
        ibloc = vbloc_of_fbloc(fd->inumber, fd->pos / HDA_SECTORSIZE, FALSE);
        write_bloc(current_vol, ibloc, fd->buf);
	
	    if (verbose)
		    printf("  writec_ifile(): write the buffer: ibloc = %d\n", ibloc);
	    
	    *//* read the new buffer*//*
        ibloc = vbloc_of_fbloc(fd->inumber,(fd->pos+1) / HDA_SECTORSIZE, FALSE);
	
	    if (verbose)
		    printf("  writec_ifile(): read the buffer: ibloc = %d\n", ibloc);
	    
        if (! ibloc)
            memset(fd->buf, 0, HDA_SECTORSIZE *//*BLOC_SIZE*//*);
        else
            read_bloc(current_vol, ibloc, fd->buf);
	    
        fd->dirty = FALSE;*/
        flush_ifile(fd);
    }

    /* update the file cursor and size */
    if (fd->size < fd->pos)
        fd->size = fd->pos;
    fd->pos++;

    /* the position of the written char */
	if (verbose)
		printf(" writec_ifile() exit... with fd->pos - 1 = %d\n",fd->pos - 1);
	
    return fd->pos - 1;
}

/*------------------------------
  Read from file
  ------------------------------------------------------------*/
int read_ifile(file_desc_t *fd, void *buf, unsigned int nbyte) {

    unsigned int i;
    int c;

    /* eof? */
    if (fd->pos >= fd->size)
        return FILE_EOF;

    /* read one by one */
    for (i = 0; i < nbyte; i++) {
        if ((c = readc_ifile(fd)) == FILE_EOF) {
            return i;
        }
        *((char *)buf+i) = c;
    }

    return i;
}

/*------------------------------
  Write to file
  ------------------------------------------------------------*/
int write_ifile(file_desc_t *fd, const void *buf, unsigned int nbyte) {

    unsigned int i;

    /* write one by one */
    for (i = 0; i < nbyte; i++) {
        if (writec_ifile(fd, *((char *)buf+i)) == -1)
            return -1;
    }

    return nbyte;
}