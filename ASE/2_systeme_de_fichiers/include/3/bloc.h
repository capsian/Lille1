#ifndef TP_BLOC_H
#define TP_BLOC_H

#define MAGIC_SB 0xDEADBEEF
#define MAGIC_FL 0xDEADBAAF
#define BLOC_NULL 0

struct super_bloc_s {
	
	unsigned int magic;
	int serial;
	char name[32];
	int num_bloc;
	int nb_free_bloc;
	int first_free_bloc;
};

struct free_bloc_s {
	
	unsigned int next_free_bloc;
	unsigned int magic;
};

extern struct super_bloc_s super_bloc;
extern unsigned int current_vol;

void init_super(unsigned int vol, int serial, char* name);
int load_super(unsigned int vol);
void save_super();
unsigned int new_bloc();
int free_bloc(unsigned int bloc);
void ls_super(unsigned int vol);
void ls_usage(unsigned int vol);

#endif
