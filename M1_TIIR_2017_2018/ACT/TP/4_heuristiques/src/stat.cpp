#include <iostream>
#include <string.h>
#include <assert.h>
#include "../include/input.h"
#include "../include/stat.h"
#include "../include/my_qsort.h"

using namespace std;

double moy_t;
double med_t;

double moy_m;
double med_m;

void med_machines() {
	
	list<task_s>::iterator it1 = input_list.begin();
	list<task_s>::iterator it2 = input_list.begin();
	
	qsort_by_machines();
	
	advance (it1,input_list.size() / 2 - 1);
	advance (it2,input_list.size() / 2);
	
	if (nb_t % 2 == 0) {
		
		med_m = (it1->nb_m_u + it2->nb_m_u) / 2 ;
	}
	else {
		
		med_m = it2->nb_m_u;
	}
	
	return;
}

void moy_machines() {

    int sum = 0;
	
	for (list<task_s>::iterator it=input_list.begin(); it!=input_list.end(); ++it)
		sum += it->nb_m_u;

    moy_m = sum / nb_t;
		
	return;
}

void med_wait(list<int> list_wait) {
	
	list<int>::iterator it1 = list_wait.begin();
	list<int>::iterator it2 = list_wait.begin();
	int tmp;
	
	advance (it1,list_wait.size() / 2 - 1);
	advance (it2,list_wait.size() / 2);
	
	if (nb_t % 2 == 0) {
		
		tmp = (*it1 + *it2) / 2 ;
	}
	else {
		tmp = *it2;
	}
	
	cout << "med_wait = " << tmp << endl;
	
	return;
}

void moy_wait(list<int> list_wait) {
	
	int sum = 0;
	
	for (list<int>::iterator it=list_wait.begin(); it!=list_wait.end(); ++it)
		sum += *it;
	
	cout << "moy_wait = " << sum / list_wait.size() << endl;
	
	return;
}

void moy_time() {

    int sum = 0;
	
	for (list<task_s>::iterator it=input_list.begin(); it!=input_list.end(); ++it)
		sum += it->time;

    moy_t = sum / nb_t;
}

void med_time() {
	
	list<task_s>::iterator it1 = input_list.begin();
	list<task_s>::iterator it2 = input_list.begin();
	
	qsort_by_time();
	advance (it1,input_list.size() / 2 - 1);
	advance (it2,input_list.size() / 2);
	
	if (nb_t % 2 == 0)
		med_t = (it1->time + it2->time) / 2 ;
	else
		med_t = it2->time;
	
	return;
}

int* paliers_machines(int* tab_paliers, int nb_val) {

    int* res = (int*) malloc(sizeof(int) * nb_val);
    assert(res != NULL);
	
    /* pour chaque paliers */
    for (int i = 0; i < nb_val - 1; i++) {

        /* init */
        res[i] = 0;

        /* pour chaque taches */
	    for (list<task_s>::iterator it=input_list.begin(); it!=input_list.end(); ++it) {
            if ((it->nb_m_u >= tab_paliers[i]) && (it->nb_m_u < tab_paliers[i+1])) {
                res[i] += 1;
            }
        }
    }

    return res;
}

int* paliers_time(int* tab_paliers, int nb_val) {

    int* res = (int*) malloc(sizeof(int) * nb_val);
    assert(res != NULL);
    /* pour chaque paliers */
    for (int i = 0; i < nb_val - 1; i++) {

        /* init */
        res[i] = 0;

        /* pour chaque taches */
	    for (list<task_s>::iterator it=input_list.begin(); it!=input_list.end(); ++it) {
            if ((it->time >= tab_paliers[i]) && (it->time < tab_paliers[i+1])) {
                res[i] += 1;
            }
        }
    }

    return res;
}

int* create_paliers(int nb, int scale) {

    int j = 0;
    int* res = (int*) malloc(sizeof(int) * (nb/scale) + 1);
	
    assert(res != NULL);

    cout << "create_paliers: nb = " << nb << ", scale = " << scale  << ", alloc = " << (nb/scale) + 1  << ", max_t = " << max_t << endl;

    for (int i = 0; i <= nb+scale ; i += scale) {
        res[j++] = i;
    }

    return res;
}

void display_stats() {
	
	int* res_plaiers1;
	int* res_plaiers2;
	int* res_p_machines;
	int* res_p_time;
	list<int> list_wait;
	
	moy_machines();
	med_machines();
	cout << "moy_machines = " << moy_m << endl;
	cout << "med_machines = " << med_m << endl;
	
	moy_time();
	med_time();
	cout << "moy_time = " << moy_t << endl;
	cout << "med_time = " << med_t << endl;

    res_plaiers1 = create_paliers(nb_m, SCALE);
	cout << "== display res_plaiers ==" << endl;
	for (int i = 0; i < ((nb_m+SCALE)/SCALE) + 1; i++) {
		cout << "palier " << i << " = " << res_plaiers1[i] << endl;
	}
	
	res_p_machines = paliers_machines(res_plaiers1, ((nb_m+SCALE)/SCALE) + 1);
	cout << "== display res_p_machines ==" << endl;
	for (int i = 0; i <= nb_m/SCALE; i++) {
		cout << "palier " << i << " = " << res_p_machines[i] << endl;
	}

    free(res_p_machines);
    free(res_plaiers1);

    res_plaiers2 = create_paliers(max_t, SCALE_TIME);
    cout << "== display paliers_time ==" << endl;
    for (int i = 0; i < ((max_t+SCALE_TIME)/SCALE_TIME) + 1; i++) {
        cout << "palier " << i << " = " << res_plaiers2[i] << endl;
    }

    res_p_time = paliers_time(res_plaiers2, ((max_t+SCALE_TIME)/SCALE_TIME) + 1);
    cout << "== display res_p_time ==" << endl;
    for (int i = 0; i <= max_t/SCALE_TIME; i++) {
        cout << "palier " << i << " = " << res_p_time[i] << endl;
    }
	
	/* WAIT */
	cout << "== display wait ==" << endl;
	for (list<task_s>::iterator it1=input_list.begin(), it2 = input_list.begin(); it2!=input_list.end(); ++it1) {
		advance(it2,1);
		list_wait.push_back(abs(it1->start - it2->start));
	}
	list_wait.sort();
	moy_wait(list_wait);
	med_wait(list_wait);
	
	free(res_plaiers2);
    free(res_p_time);
}
