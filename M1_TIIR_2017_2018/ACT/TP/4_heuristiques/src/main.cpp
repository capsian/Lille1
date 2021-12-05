#include <iostream>
#include <string.h>
#include <stdlib.h>

#include "../include/input.h"
#include "../include/calculate.h"
#include "../include/stat.h"
#include "../include/first_try.h"
#include "../include/my_qsort.h"

using namespace std;

char file_name[50];

void usage() {

    cout << "ERROR usage()" << endl;
    exit(EXIT_FAILURE);
}

int main(int argc, char** argv) {
	
	if (argc < 2) {
		usage();
	}
	
	strcpy(file_name,argv[1]);
	input(file_name);
	
	if (argc == 3) {
		display_stats();
		return 0;
	}
	
	process();
	
	task_s* input_tab     = (task_s*) malloc(sizeof(task_s) * nb_t);
	int i = 0;
	for (list<task_s>::iterator it = res.begin (); it != res.end (); ++it)
		input_tab[i++] = *it;
	
	int* tmp_res = calculate(input_tab);
	
	/*display_tab(input_tab);*/
	display_res(tmp_res);
	/*display_list (res);*/
    
    return 0;
}