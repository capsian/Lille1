#ifndef MALLOC_H
#define MALLOC_H

#define NULL 0

#define NB_BLOCKS 50
#define Mo (1024*1024)
#define MSIZE 100000
extern void * next_free_memory;
extern char memory[16*Mo];
extern char * top_heap;
struct free_block_s {
  int size;
  char * base_address;
  int free;
};
extern struct free_block_s blocks[NB_BLOCKS];
void * malloc(int size);
void free(void * adr);
#endif
