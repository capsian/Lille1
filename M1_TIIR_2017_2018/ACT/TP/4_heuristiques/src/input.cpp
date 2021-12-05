#include <iostream>
#include <stdio.h>

#include "../include/input.h"
#include "../include/first_try.h"

using namespace std;

int nb_m;
int nb_t;
int max_t = 0;

list<task_s> input_list;
FILE* input_f;

void input(char* input_file) {
	
    input_f = fopen (input_file,"r");

	fscanf(input_f,"%d\n%d\n",&nb_m, &nb_t);
    for (int i = 0; i < nb_t; i++) {
        task_s tmp;
        fscanf(input_f,"%d %d %d\n",&tmp.start, &tmp.nb_m_u, &tmp.time);
        tmp.ordre = i;

        tmp.score_surface = score_surface(tmp.start, tmp.nb_m_u, tmp.time, nb_m, 0, i);
        tmp.is_taken = 0;
	    tmp.nb_m_u_tmp = tmp.nb_m_u;
        
	    if (tmp.time > max_t)
            max_t = tmp.time;
	    
        input_list.push_back(tmp);
    }

    fclose(input_f);
}

void display_list(list<task_s> l) {
	
	int cpt= 0;

    cout << "== display_list ==" << endl;
    for (list<task_s>::iterator it=l.begin(); it!=l.end(); ++it){
        cout << it->ordre << ": " << "start: " << it->start << "\tnb_m: " << it->nb_m_u << "\ttime:" <<  it->time;
	    cout << "\tsurface = " << it->score_surface;
	    cout << endl;
	    
	    /*if (cpt ++ == 50)
		    break;*/
    }

    return;
}

void display_tab(task_s* tab) {
	
	int cpt= 0;
	
	cout << "== display_tab ==" << endl;
	for (int i = 0; i<nb_t; i++){
		cout << tab[i].ordre << ": " << "start: " << tab[i].start << "\tnb_m: " << tab[i].nb_m_u << "\ttime:" <<  tab[i].time;
		cout << "\tsurface = " << tab[i].score_surface;
		cout << endl;
	}
	
	return;
}