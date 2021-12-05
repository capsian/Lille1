#include <iostream>
#include "../include/fifo.h"

using namespace std;

list<fin_machine>::iterator it;
fin_machine VIDE;
list<fin_machine> fifo;

void enfile_at(int temps_fin, int nombre_machines) {

  fin_machine tmp;
  tmp.fin_tache = temps_fin;
  tmp.nombre_machines = nombre_machines;

  for (it = fifo.begin(); it != fifo.end(); it++) {
    if(it->fin_tache >= temps_fin){

      fifo.insert(it,tmp);
      return;
    }
  }

  fifo.insert(it,tmp);
}

fin_machine defile() {

  if (!fifo.empty()) {

    fin_machine ret;
    ret = fifo.front();
    fifo.pop_front();

    return ret;
  }

  VIDE.fin_tache = -1;
  VIDE.nombre_machines = -1;

  return VIDE;
}

void print_struct_fin_machine(fin_machine tmp) {

  cout << "Fin tache : " << tmp.fin_tache << " Nb Machines " << tmp.nombre_machines << endl;

}