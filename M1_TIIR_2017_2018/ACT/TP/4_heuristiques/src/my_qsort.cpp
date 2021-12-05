#include <iostream>
#include <stdlib.h>

#include "../include/input.h"

using namespace std;

bool compare_machines (const task_s& a, const task_s& b) {
	
	return ( a.nb_m_u < b.nb_m_u );
}

bool compare_time (const task_s& a, const task_s& b) {
	
	return ( a.time < b.time );
}

bool compare_score_surface (const task_s& a, const task_s& b) {
    
    return ( a.score_surface < b.score_surface);
}

void qsort_by_machines() {
	input_list.sort(compare_machines);
}

void qsort_by_time() {
	input_list.sort(compare_time);
}

void qsort_by_score_surface() {
	input_list.sort(compare_score_surface);
}