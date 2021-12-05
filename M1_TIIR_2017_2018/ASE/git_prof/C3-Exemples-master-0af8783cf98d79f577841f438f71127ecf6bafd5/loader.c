#include <stdio.h>
#include <sys/mman.h>
#include <assert.h>
#include <elf.h>

typedef int (entrypoint)(int argc, char**argv);

int main(int argc, char **argv) {
  FILE *fl;
  int file_size,offset,res;
  unsigned char *elf;
  entrypoint *fct;
  /* 1. read the elf file */
  printf("read \"loaded\" file :\n");
  fl=fopen("loaded","rb");
  fseek(fl,0L,SEEK_END);
  file_size=ftell(fl);
  fseek(fl,0L,SEEK_SET);
  elf=mmap(NULL, file_size, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
  fread(elf,file_size,1,fl);
  printf(" ... %d (0x%x) bytes\n",file_size,file_size);
  fclose(fl);
  /* 2. find entry-point */
  offset=*((long int*)&elf[24]);
  fct=(void *)(elf+offset);
  printf("find the entrypoint :\n");
  printf(" ... at offset 0x%x \n",offset);
  assert(elf[0]==0x7f&&elf[1]=='E'&&elf[2]=='L'&&elf[3]=='F');
  assert(fct!=(void *)elf);
  printf("call it!\n");
  res=fct(0,NULL);
  printf("return %d\n",res);
  return 0;
}
