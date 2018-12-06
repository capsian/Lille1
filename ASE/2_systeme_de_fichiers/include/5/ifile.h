#ifndef ASE_PC_IFILE_H
#define ASE_PC_IFILE_H

#include "../../include/1/drive.h"
#include "../../include/4/inode.h"

#define FILE_EOF -1

struct file_desc_s {

    unsigned int inumber;
    unsigned int pos;
    unsigned char buf[HDA_SECTORSIZE];
    unsigned int dirty; /* if buffer is used */
    unsigned int size; /* size of file for EOF */
};

typedef struct file_desc_s file_desc_t;


unsigned int create_ifile(enum file_type_e type);
int delete_ifile(unsigned int inumber);

int open_ifile(file_desc_t* fd, unsigned int inum);
void close_ifile(file_desc_t* fd);
void flush_ifile(file_desc_t *fd);

void seek_ifile(file_desc_t *fd, int offset);
void seek2_ifile(file_desc_t *fd, int offset);

int readc_ifile(file_desc_t *fd);
int writec_ifile(file_desc_t *fd, unsigned char c);

int read_ifile(file_desc_t *fd, void *buf, unsigned int nbyte);
int write_ifile(file_desc_t *fd, const void *buf, unsigned int nbyte);

#endif
