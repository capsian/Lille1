#ifndef ACT_INPUT_H
#define ACT_INPUT_H

#include <stdlib.h>
#include <list>

typedef struct task_s {

    int ordre;
    int start;
    int nb_m_u;
    int nb_m_u_tmp;
    int time;
    
    long long int score_surface;
    int is_taken;

}task_s;

extern int nb_m;
extern int nb_t;
extern int max_t;
extern std::list<task_s> input_list;

void input(char* input_file);
void display_list(std::list<task_s> l);
void display_tab(task_s* tab);

#endif
