#ifndef SEMAPHORE_H
#define SEMAPHORE_H

struct sem_s {
  struct ctx_s * bloquer;
  int compteur;
};

void sem_init(struct sem_s *,unsigned int);
void sem_down(struct sem_s *);
void sem_up(struct sem_s *);
extern struct ctx_s * current_ctx;

#endif
