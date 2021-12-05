#include <iostream>

#include "../include/input.h"
#include "../include/stat.h"
#include "../include/my_qsort.h"
#include "../include/first_try.h"
#include <list>

using namespace std;

list<task_s> res;

long unsigned int score_surface(int start, int nb_m_u, int time, int curr_m, long long int curr_t, int ordre) {
	
	if (nb_m_u > curr_m)
		return 0xFFFFFFFFF;
	else
		return curr_t*curr_m - nb_m_u*(abs(start - time));
		return abs((time* nb_m_u) - ((curr_t+1)*curr_m)) + start;
		return (time* nb_m_u) + start*10 + (curr_t*100);
}

void calculate_score(int curr_m, long long int curr_t) {
	
	for (list<task_s>::iterator it = input_list.begin (); it != input_list.end (); ++it)
		it->score_surface = score_surface(it->start, it->nb_m_u, it->time, curr_m, curr_t, it->ordre);
}

void free_machines(int* curr_m, long long int* curr_t) {
	
	for (list<task_s>::iterator it = res.begin (); it != res.end (); ++it) {
		if (it->nb_m_u_tmp != 0) {
			
			*curr_m += it->nb_m_u;
			it->nb_m_u_tmp = 0;
			*curr_t += it->start + it->time;
			return; /* freeing one machine */
		}
	}
}

void process() {
	
	int curr_m = nb_m;
	long long int curr_t = 0;
	int cpt = 0;
	task_s tmp;
	
	while (!input_list.empty()) {
		
		calculate_score(curr_m, curr_t);
		qsort_by_score_surface();
		
		/*cout << "curr_m = " << curr_m << ", curr_t = " << curr_t << endl;
		display_list(input_list);*/
		
		tmp = input_list.front();
		
		if (tmp.nb_m_u <= curr_m) {
			
			res.push_back(tmp);
			input_list.pop_front();
			
			curr_m -= tmp.nb_m_u;
			
		} else {
			free_machines (&curr_m, &curr_t);
		}
		
		/*cout << "###############################" << endl;
		display_list(res);
		cout << "###############################" << endl;
		
		if (cpt++ == 50)
			break;*/
	}
}
