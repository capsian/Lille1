#ifndef TP_DRIVE_H
#define TP_DRIVE_H

#define HWCONFIG "../etc/hwconfig.ini"

#define HDA_CMDREG	    0x3F6
#define HDA_DATAREGS	0x110
#define HDA_IRQ	        14
#define HDA_MAXCYLINDER	16
#define HDA_MAXSECTOR	16
#define HDA_SECTORSIZE	256


void setup();

void seek(int, int);

void read_sector(unsigned int, unsigned int, unsigned char*);
void write_sector(unsigned int, unsigned int, unsigned char*);
void format_sector(unsigned int cylinder, unsigned int sector, unsigned int value);

void read_sector_n(unsigned int cylinder, unsigned int sector, unsigned int size, unsigned char* buffer);
void write_sector_n(unsigned int cylinder, unsigned int sector, unsigned int size, unsigned char* buffer);

#endif
