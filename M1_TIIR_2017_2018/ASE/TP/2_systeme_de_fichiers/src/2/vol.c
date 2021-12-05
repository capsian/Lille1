#include <stdio.h>
#include <assert.h>

#include "../../include/1/drive.h"
#include "../../include/2/vol.h"
#include "../../include/2/mbr.h"

int cyl_of_bloc(int vol, int bloc) {
	
	return (gMBR.vol[vol].num_cyl + ( gMBR.vol[vol].num_sec + bloc) / HDA_MAXSECTOR);
}

int sec_of_bloc(int vol, int bloc) {
	
	return (gMBR.vol[vol].num_sec + bloc) % HDA_MAXSECTOR;
}

void read_bloc(int vol, int bloc, unsigned char* buffer) {
	
	assert(gMBR.magic == MAGIC);
	
	read_sector(cyl_of_bloc(vol,bloc), sec_of_bloc(vol,bloc), buffer);
}

void write_bloc(int vol, int bloc, unsigned char* buffer) {
	
	assert(gMBR.magic == MAGIC);
	
	write_sector(cyl_of_bloc(vol,bloc), sec_of_bloc(vol,bloc), buffer);
}

void read_bloc_n(int vol, int bloc, unsigned int size, unsigned char* buffer) {
	
	assert(gMBR.magic == MAGIC);
	
	read_sector_n(cyl_of_bloc(vol,bloc), sec_of_bloc(vol,bloc), size, buffer);
}

void write_bloc_n(int vol, int bloc, unsigned int size, unsigned char* buffer) {
	
	assert(gMBR.magic == MAGIC);
	
	write_sector_n(cyl_of_bloc(vol,bloc), sec_of_bloc(vol,bloc), size, buffer);
}