#include <iostream>

#include "../include/fifo.h"
#include "../include/input.h"

using namespace std;

int* calculate(task_s* input_tab) {
    
    int tmp_start;
    int current_machines = nb_m;
    int t = 0;
    int* res = (int*) malloc(sizeof(int) * nb_t);
    fin_machine tmp_f_m;

    for (int i = 0; i < nb_t; i++) {

        /* assez de machines pour exec la tache */
        if (input_tab[i].nb_m_u <= current_machines) {
	        
            if(t >= input_tab[i].start)
                tmp_start = t;
            else
                tmp_start = input_tab[i].start;
            
            enfile_at(tmp_start + input_tab[i].time, input_tab[i].nb_m_u );
            current_machines -= input_tab[i].nb_m_u;
            res[input_tab[i].ordre] = tmp_start;
        }
        else {

            while (current_machines < input_tab[i].nb_m_u)  { /* check <= */

                tmp_f_m = defile();
                current_machines += tmp_f_m.nombre_machines;
                t = tmp_f_m.fin_tache;
            }
	        
            if(t >= input_tab[i].start) {
                tmp_start = t;
            } else {
                tmp_start = input_tab[i].start;
            }
	        
            enfile_at(tmp_start + input_tab[i].time, input_tab[i].nb_m_u );
            current_machines -= input_tab[i].nb_m_u;
            res[input_tab[i].ordre] = tmp_start;
        }
    }

    return res;
}

void display_res(int* tab) {
	
	for (int i = 0; i < nb_t; i++) {
		cout << tab[i] << endl;
	}
}