#include <stdio.h>
#include "../include/semaphore.h"
#include "../include/tmr.h"

sem_s f1, f2, f3, f4;

void penser(int i) {
  printf("%d pense .\n",i);
  for (int i = 0; i < 3200; i++);
}

void manger(int i) {

  printf("%d mange .\n",i);
  for (int i = 0; i < 3200; i++);
}

void philosophe1 () {
  while(1) {

    penser(1);
    printf("philosophe1 essaie de prende f1 ... \n");
    sem_down(&f1);
    printf("philosophe1 essaie de prende f2 ... \n");
    sem_down(&f2);
    manger(1);
    printf("philosophe1 rend f2 ... \n");
    sem_up(&f2);
    printf("philosophe1 rend f1 ... \n");
    sem_up(&f1);

  }
}

void philosophe2 () {
  while(1) {

    penser(2);
    printf("philosophe2 essaie de prende f2 ... \n");
    sem_down(&f2);
    printf("philosophe2 essaie de prende f3 ... \n");
    sem_down(&f3);
    manger(2);
    printf("philosophe2 rend f3 ... \n");
    sem_up(&f3);
    printf("philosophe2 rend f2 ... \n");
    sem_up(&f2);
  }
}

void philosophe3 () {
  while(1) {

    penser(3);
    printf("philosophe3 essaie de prende f3 ... \n");
    sem_down(&f3);
    printf("philosophe3 essaie de prende f4 ... \n");
    sem_down(&f4);
    manger(3);
    printf("philosophe3 rend f4 ... \n");
    sem_up(&f4);
    printf("philosophe3 rend f3 ... \n");
    sem_up(&f3);
  }
}

void philosophe4 () {
  while(1) {

    penser(4);
    printf("philosophe4 essaie de prende f4 ... \n");
    sem_down(&f4);
    printf("philosophe4 essaie de prende f1 ... \n");
    sem_down(&f1);
    manger(4);
    printf("philosophe4 rend f1 ... \n");
    sem_up(&f1);
    printf("philosophe4 rend f4 ... \n");
    sem_up(&f4);
  }
}

int main() {

  current_ctx = NULL;

  sem_init(&f1, 1);
  sem_init(&f2, 1);
  sem_init(&f3, 1);
  sem_init(&f4, 1);

  create_ctx(65536,philosophe1,NULL);
  create_ctx(65536,philosophe2,NULL);
  create_ctx(65536,philosophe3,NULL);
  create_ctx(65536,philosophe4,NULL);

  start_sched(yield);

  return 0;
}
