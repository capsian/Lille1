#ifndef TP_UTILS_H
#define TP_UTILS_H

#define MAX_TASKS    15

extern int matrix[MAX_TASKS][2];
extern int certif[MAX_TASKS][2];

extern int tasks[MAX_TASKS];
extern int nb_m, nb_t, d;

void display_matrix();
void display_certif();
void display_tasks();

void input_part(char* tasks_file);
void input_tasks(char* input_file);
void input_certif();

#endif
