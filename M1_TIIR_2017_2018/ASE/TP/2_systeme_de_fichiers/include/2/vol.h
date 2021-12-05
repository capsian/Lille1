#ifndef TP_VOL_H
#define TP_VOL_H

int sec_of_bloc(int vol, int bloc);
int cyl_of_bloc(int vol, int bloc);

void read_bloc(int vol, int bloc, unsigned char* buffer);
void read_bloc_n(int vol, int bloc, unsigned int size, unsigned char* buffer);

void write_bloc(int vol, int bloc, unsigned char* buffer);
void write_bloc_n(int vol, int bloc, unsigned int size, unsigned char* buffer);


#endif
