#ifndef ACT_STAT_H
#define ACT_STAT_H

#define SCALE 10
#define SCALE_TIME 50000

void moy_machines();
void med_machines();

void moy_time();
void med_time();

int* create_paliers(int nb, int scale);
int* paliers_time(int* tab_paliers, int nb_val);
int* paliers_machines(int* tab_paliers, int nb_val);


void display_stats();

extern double moy_m;
extern double med_m;

extern double moy_t;
extern double med_t;

#endif
