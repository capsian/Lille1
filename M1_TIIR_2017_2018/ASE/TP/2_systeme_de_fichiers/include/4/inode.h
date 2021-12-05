#ifndef ASE_PC_INODE_H
#define ASE_PC_INODE_H

#include "../1/drive.h"
#include "../utils.h"

#define MAGIC_INODE 0x12345678
#define NB_DIRECT ((HDA_SECTORSIZE - sizeof(int) * 4 - sizeof(enum file_type_e)) / sizeof(int))
#define NB_INDIRECT (HDA_SECTORSIZE / sizeof(int))
#define BLOC_NULL 0

enum file_type_e {
    file,
    directory
};

struct inode_s {
    int magic;
    enum file_type_e type;
    unsigned int size;
    unsigned int direct[NB_DIRECT];
    unsigned int indirect;
    unsigned int indirect2;
};

void read_inode(unsigned int inumber, struct inode_s *inode);
void write_inode(unsigned int inumber, struct inode_s *inode);
unsigned int create_inode(enum file_type_e type);
void free_indirect(unsigned int indirectn);
void delete_inode(unsigned int inumber);
unsigned int vbloc_of_fbloc(unsigned int inumber, unsigned int fbloc, bool_t do_allocate);

#endif
