#include <stdlib.h>
#include <stdio.h>

#include "../../include/1/drive.h"
#include "../../include/utils.h"
#include "../../include/hardware.h"

unsigned int i;

void setup() {
	
	int i;
	
	/* init hardware */
	if(init_hardware(HWCONFIG) == 0) {
		fprintf(stderr, "Error in hardware initialization\n");
		exit(EXIT_FAILURE);
	}
	
	/* Interrupt handlers */
	for(i=0; i<16; i++)
		IRQVECTOR[i] = empty_it;
	
	/* Allows all IT */
	_mask(1);
}

void seek(int cyl, int sec) {

  _out(0x110, (cyl & 0x0000FF00) >> 8);
  _out(0x111, (cyl & 0x000000FF));

  _out(0x112, (sec & 0x0000FF00) >> 8);
  _out(0x113, (sec & 0x000000FF));

  _out(HDA_CMDREG,CMD_SEEK);
  _sleep(HDA_IRQ);
}

void read_sector(unsigned int cylinder, unsigned int sector, unsigned char* buffer) {

  seek(cylinder,sector);
  
  _out(0x110, 0);
  _out(0x111, 1);
	
  clean_buffer(MASTERBUFFER);
  clean_buffer(buffer);

  _out(HDA_CMDREG, CMD_READ);

  _sleep(HDA_IRQ);

  for (i = 0; i < HDA_SECTORSIZE; i++)
      buffer[i] = MASTERBUFFER[i];

}

void write_sector(unsigned int cylinder, unsigned int sector, unsigned char* buffer) {
	
  seek(cylinder,sector);
  
  _out(0x110, 0);
  _out(0x111, 1);
	
  clean_buffer(MASTERBUFFER);

  /* COPY FROM BUFEER */
  for (i = 0; i < HDA_SECTORSIZE; i++)
      MASTERBUFFER[i] = buffer[i];

  _out(HDA_CMDREG, CMD_WRITE);
  _sleep(HDA_IRQ);
}

void read_sector_n(unsigned int cylinder, unsigned int sector, unsigned int size, unsigned char* buffer) {
	
	seek(cylinder,sector);
	
	_out(0x110, 0);
	_out(0x111, 1);
	
	clean_buffer(MASTERBUFFER);
	/*clean_buffer(buffer);*/
	
	_out(HDA_CMDREG, CMD_READ);
	
	_sleep(HDA_IRQ);
	
	for (i = 0; i < size; i++)
		buffer[i] = MASTERBUFFER[i];
}

void write_sector_n(unsigned int cylinder, unsigned int sector, unsigned int size, unsigned char* buffer) {
	
	seek(cylinder,sector);
	
	_out(0x110, 0);
	_out(0x111, 1);
	
	clean_buffer(MASTERBUFFER);
	
	/* COPY FROM BUFEER */
	for (i = 0; i < size; i++)
		MASTERBUFFER[i] = buffer[i];
	
	_out(HDA_CMDREG, CMD_WRITE);
	_sleep(HDA_IRQ);
}

void format_sector(unsigned int cylinder, unsigned int sector, unsigned int value) {
	
	seek(cylinder, sector);
	
	/* Nombre de secteurs */
	_out(HDA_DATAREGS, 0);
	_out(HDA_DATAREGS+1, 1);
	
	/* Value sur 32 bits */
	_out(HDA_DATAREGS+2, (value & 0xFF00) >> 8);
	_out(HDA_DATAREGS+3, (value & 0xFF));
	_out(HDA_DATAREGS+4, (value & 0xFF00) >> 8);
	_out(HDA_DATAREGS+5, (value & 0xFF));
	
	_out(HDA_CMDREG, CMD_FORMAT);
	_sleep(HDA_IRQ);
}