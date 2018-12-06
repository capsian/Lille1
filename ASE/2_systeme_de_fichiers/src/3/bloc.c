#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "../../include/3/bloc.h"
#include "../../include/2/mbr.h"
#include "../../include/2/vol.h"
#include "../../include/utils.h"

struct super_bloc_s super_bloc;
unsigned int current_vol = 0;

void init_super(unsigned int vol, int serial, char* name) {

	int i;
	struct free_bloc_s free_bloc;

    if (verbose)
        printf(" init_super() enter ...\n");
	
	super_bloc.magic = MAGIC_SB;
	super_bloc.serial = serial;
	super_bloc.num_bloc = BLOC_NULL;
	super_bloc.nb_free_bloc = gMBR.vol[vol].nb_bloc - 1;
	super_bloc.first_free_bloc = 1;
	strcpy(super_bloc.name,name);
	
	if (verbose) {
		
		printf("  super_bloc inited !\n");
		printf("   initial nb_bloc from mbr = %d\n",gMBR.vol[vol].nb_bloc);
		printf("   super_bloc.magic = %d | super_bloc.serial = %d | super_bloc.num_bloc = %d | super_bloc.nb_free_bloc = %d\n", super_bloc.magic, super_bloc.serial, super_bloc.num_bloc, super_bloc.nb_free_bloc);
		printf("   super_bloc.first_free_bloc = %d | super_bloc.name = %s\n",super_bloc.first_free_bloc, super_bloc.name);
		printf("  linking the free_list ....\n");
	}
	
	for (i=1; i<gMBR.vol[vol].nb_bloc - 1; i++) {
		
		free_bloc.magic = MAGIC_FL;
		free_bloc.next_free_bloc = i+1;
		write_bloc_n(vol, i, sizeof(free_bloc), (unsigned char*) &free_bloc);
		
		if (verbose) {
			printf("   link bloc %d with bloc %d\n", i, i+1);
		}
	}

	if (verbose) {
		
		printf("   linking the last one !\n");
		printf("   linking %d\n",i);
	}
	
    free_bloc.next_free_bloc = 0;
    free_bloc.next_free_bloc = 1;  /*for the delete case*/
	write_bloc_n(vol, i, sizeof(free_bloc), (unsigned char*) &free_bloc);
	
	current_vol = vol;
	save_super();

    if (verbose)
        printf(" init_super() exit ...\n");
}

int load_super(unsigned int vol) {

    if (verbose)
        printf(" load_super() enter ...\n");

	if (vol >= gMBR.nbVol) {
		
		if (verbose)
			printf("  [ERROR] load_super() exit with error ... | vol >= gMBR.nbVol\n");
		
		return 0;
	}
	
	read_bloc_n(vol,0, sizeof(super_bloc),(unsigned char*) &super_bloc);
	
	if (super_bloc.magic != MAGIC_SB) {
		
        if (verbose) {
	
	        printf("  [ERROR] load_super() exit with error ... | super_bloc.magic != MAGIC_SB\n");
	        printf("    initial nb_bloc from mbr = %d\n",gMBR.vol[vol].nb_bloc);
	        printf("    super_bloc.magic = %d | super_bloc.serial = %d | super_bloc.num_bloc = %d | super_bloc.nb_free_bloc = %d\n", super_bloc.magic, super_bloc.serial, super_bloc.num_bloc, super_bloc.nb_free_bloc);
	        printf("    super_bloc.first_free_bloc = %d | super_bloc.name = %s\n",super_bloc.first_free_bloc, super_bloc.name);
        }
		return 0;
    }
	
	current_vol = vol;

    if (verbose)
        printf(" load_super() exit normally ...\n");

	return 1;
}

void save_super() {

    if (verbose) {
	    
	    printf(" save_super() enter ...\n");
	    printf("  saving vol: %s , serial = %d, magic = %d\n",super_bloc.name, super_bloc.serial, super_bloc.magic);
    }

	write_bloc_n(current_vol,0, sizeof(super_bloc), (unsigned char*) &super_bloc);

    if (verbose)
        printf(" save_super() exit ...\n");
}

unsigned int new_bloc() {

	unsigned int res;
	struct free_bloc_s free_list;

    if (verbose)
        printf(" new_bloc() enter ...\n");

	assert(super_bloc.magic == MAGIC_SB);
	
	res = super_bloc.first_free_bloc;
	if ((res == BLOC_NULL)|| (super_bloc.nb_free_bloc == 0)) {

        if (verbose)
            printf(" new_bloc() exit with error ... | FULL SPACE\n");

        return BLOC_NULL;
    }

	read_bloc_n(current_vol, res, sizeof(free_list), (unsigned char*) &free_list);
	super_bloc.first_free_bloc = free_list.next_free_bloc;
    super_bloc.nb_free_bloc--;
	save_super();

    if (verbose)
        printf(" new_bloc() exit with new bloc ... with bloc_num = %d\n", res);

	return res;
}

int free_bloc(unsigned int bloc) {
	
	struct free_bloc_s bloc_list;
	unsigned int tmp_bloc;

    if (verbose)
        printf(" free_bloc() enter ... | current_vol = %d\n",current_vol);
	
	assert(super_bloc.magic == MAGIC_SB);
	if (load_super(current_vol) == 0) {
		
		if (verbose)
			printf("  [ERROR] free_bloc() exit ... | load_super(%d) returned 0\n",current_vol);
		return 0;
	}
	
	if (bloc >= (unsigned int)gMBR.vol[current_vol].nb_bloc) {
		
		if (verbose)
			printf("  [ERROR] free_bloc() exit ... | bloc(%d) >= nb_bloc(%d)\n",bloc, gMBR.vol[current_vol].nb_bloc);
		return 0;
	}
	
	if (super_bloc.nb_free_bloc == gMBR.vol[current_vol].nb_bloc - 1) {
		if (verbose)
			printf("  [ERROR] free_bloc() exit ... | already empty !!\n");
		return 0;
	}
	
	read_bloc_n(current_vol, super_bloc.first_free_bloc, sizeof(bloc_list), (unsigned char*) &bloc_list);
	
	assert(bloc_list.magic == MAGIC_FL);
	
	tmp_bloc = bloc_list.next_free_bloc;
	bloc_list.next_free_bloc = bloc;
	read_bloc_n(current_vol, bloc, sizeof(bloc_list), (unsigned char*) &bloc_list);
	bloc_list.next_free_bloc = tmp_bloc;
	write_bloc_n(current_vol, bloc, sizeof(bloc_list), (unsigned char*) &bloc_list);
	
	super_bloc.nb_free_bloc++;
	save_super();
	
    if (verbose)
        printf(" free_bloc() exit normally ...\n");
	
	return 1;
}

void ls_super(unsigned int vol) {

    if (verbose)
        printf(" ls_super() enter ...\n");

    load_super(vol);

    printf("vol : %s\n", super_bloc.name);
    printf("serial : %d\n", super_bloc.serial);
    printf("num_bloc : %d\n", super_bloc.num_bloc);
    printf("nb_free_bloc : %d\n", super_bloc.nb_free_bloc);
    printf("first_free_bloc : %d\n", super_bloc.first_free_bloc);

    if (verbose)
        printf(" ls_super() exit ...\n");
}

void ls_usage(unsigned int vol) {
	
	if (verbose)
		printf(" ls_usage() enter ...\n");
	
	load_super(vol);
	
	printf("vol: %s, serial: %d\n", super_bloc.name, super_bloc.serial);
	printf("used: %d, free: %d, totale: %d\n-------------------\n", gMBR.vol[vol].nb_bloc - super_bloc.nb_free_bloc, super_bloc.nb_free_bloc, gMBR.vol[vol].nb_bloc);
	
	if (verbose)
		printf(" ls_usage() exit ...\n");
}