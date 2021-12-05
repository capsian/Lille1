#ifndef ACT_FIFO_H
#define ACT_FIFO_H

#include <list>

using namespace std;

typedef struct fin_machine_s {
  int fin_tache;
  int nombre_machines;
}fin_machine;

extern list<fin_machine> fifo;
extern list<fin_machine>::iterator it;
extern fin_machine VIDE;

fin_machine defile();
void enfile_at(int temps_fin, int nombre_machines);
void print_struct_fin_machine(fin_machine tmp);

#endif
