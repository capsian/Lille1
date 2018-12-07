#include "../include/semaphore.h"
#include "../include/prod_cons.h"
#include "../include/tmr.h"
#include <stdio.h>

#define N 100
objet_t tampon[N];
int k = 0;

sem_s mutex, vide, plein;

int main() {

  current_ctx = NULL;

  sem_init(&mutex, 1);
  sem_init(&vide, N);
  sem_init(&plein, 0);

  create_ctx(65536,producteur,NULL);
  create_ctx(65536,consommateur,NULL);
  start_sched(yield);

  return 0;
}

void producteur (void) {

  objet_t objet;

  while (1) {

    produire_objet(&objet);
    sem_down(&vide);
    sem_down(&mutex);
    mettre_objet(objet);
    sem_up(&mutex);
    sem_up(&plein);
  }
}

void consommateur (void) {

  objet_t objet;

  while(1) {

    sem_down(&plein);
    sem_down(&mutex);
    retirer_objet(&objet);
    sem_up(&mutex);
    sem_up(&vide);
    utiliser_objet(objet);
  }
}

static int i = 0;

void produire_objet(objet_t* objet) {

  *objet = 'A' + (i);
  i = (i +1) % 26;

}

void mettre_objet(objet_t objet) {
  tampon[k++] = objet;
  printf("J'ai produit %c\n", objet);
}

void retirer_objet(objet_t* objet) {
  *objet = tampon[--k];
}

void utiliser_objet(objet_t objet) {
  printf("J'utilise %c \n",objet);
}
