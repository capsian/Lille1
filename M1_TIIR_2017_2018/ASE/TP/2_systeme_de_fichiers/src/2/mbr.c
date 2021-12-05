#include <stdio.h>
#include <assert.h>
#include "../../include/2/mbr.h"
#include "../../include/2/vol.h"
#include "../../include/1/drive.h"
#include "../../include/utils.h"

struct mbr_s gMBR;

void save_mbr() {
	
	assert(gMBR.magic == MAGIC);
	
	write_sector_n(0,0,sizeof(gMBR),(unsigned char*)&gMBR);
}

void load_mbr() {
	
	read_sector_n(0,0,sizeof(gMBR),(unsigned char*)&gMBR);
	
	if (gMBR.magic != MAGIC) {
		gMBR.magic = MAGIC;
		gMBR.nbVol = 0;
	}
}

char* display_type(unsigned int t) {
	
	switch (t) {
		case 0:
			return "VOL_BASE";
		case 1:
			return "VOL_ANNEXE";
		case 2:
			return "OTHER";
		default:
			return "UNKOWN";
	}
}

void format_vol(unsigned int v) {
	
	int i;
	
	assert(gMBR.magic == MAGIC);
	
	if (v > gMBR.nbVol) {
		printf("incorrect vol\n");
		return;
	}
	
	for (i=0; i < gMBR.vol[v].nb_bloc; i++ )
		format_sector(cyl_of_bloc(v,i),sec_of_bloc(v,i),0);

}

void ls_vol() {
	
	unsigned int i;
	int j;
	
	assert(gMBR.magic == MAGIC);
	
	for (i = 0; i < gMBR.nbVol; i++) {
		printf("Vol %d | type: %s\t nbBloc: %d\n",i, display_type(gMBR.vol[i].type), gMBR.vol[i].nb_bloc);
		printf(" first sector: %d, first cylinder: %d \t |",gMBR.vol[i].num_sec, gMBR.vol[i].num_cyl);
		
		if (verbose)
			for (j = 0; j < gMBR.vol[i].nb_bloc ; j++)
				printf("\n   bloc %d = (%d,%d)",j,sec_of_bloc(i,j), cyl_of_bloc(i,j));
		
		printf(" last sector: %d, last cylinder: %d\n",sec_of_bloc(i,gMBR.vol[i].nb_bloc), cyl_of_bloc(i,gMBR.vol[i].nb_bloc));
	}
	
	if (!i) {
		printf("NO VOL\n");
	}
	
	return;
}

void ls_specific_vol(unsigned int vol) {

    assert(gMBR.magic == MAGIC);

    if (vol >= gMBR.nbVol) {
        printf("INVALID VOL\n");
        return;
    }

    printf("Vol %d :\n type: %s\t nbBloc: %d\n",vol, display_type(gMBR.vol[vol].type), gMBR.vol[vol].nb_bloc);
    printf(" first sector: %d\t first cylinder: %d\n",gMBR.vol[vol].num_sec, gMBR.vol[vol].num_cyl);
    printf(" last sector: %d\t last cylinder: %d\n",sec_of_bloc(vol,gMBR.vol[vol].nb_bloc), cyl_of_bloc(vol,gMBR.vol[vol].nb_bloc));

    return;
}

void mkvol(unsigned int bSize, unsigned int cyl, unsigned int sec, unsigned int type) {
	
	assert(gMBR.magic == MAGIC);
	
	if (gMBR.nbVol == MAX_VOL) {
		printf("MAX VOL reached !!\n");
		return;
	}
	
	check_input(cyl,sec);
	
	gMBR.vol[gMBR.nbVol].nb_bloc = bSize;
	gMBR.vol[gMBR.nbVol].num_cyl = cyl;
	gMBR.vol[gMBR.nbVol].num_sec = sec;
	gMBR.vol[gMBR.nbVol].type = type;
	gMBR.nbVol++;
}

void del_vol(unsigned int v) {
	
	unsigned int i;
	
	assert(gMBR.magic == MAGIC);
	
	if (gMBR.nbVol < v) {
		printf("INVALID vol !!\n");
		return;
	}
	
	/* delete last one */
	if (gMBR.nbVol == v) {
		gMBR.nbVol--;
		return;
	}
	
	/* shift */
	for (i = v; i < gMBR.nbVol - 1; i++) {
		gMBR.vol[i].num_sec = gMBR.vol[i+1].num_sec;
		gMBR.vol[i].num_cyl = gMBR.vol[i+1].num_cyl;
		gMBR.vol[i].nb_bloc = gMBR.vol[i+1].nb_bloc;
		gMBR.vol[i].type    = gMBR.vol[i+1].type;
	}
	gMBR.nbVol--;

	return;
}
