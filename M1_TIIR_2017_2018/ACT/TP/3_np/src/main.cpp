#include <iostream>
#include <string.h>
#include <cstdlib>
#include <stdio.h>
#include "utils.h"
#include "british_museum.h"
#include "np.h"
#include "tree.h"

#define VERIF       "verif"
#define NONDET      "nondet"
#define EXHAUST     "exhaust"
#define PART        "part"

tGraphe graphe;

using namespace std;

int main(int argc, char** argv) {

	int wait = -1;
	char mode[10];
	char tasks_file[255];

	if (argc < 3) {
		printf("ERROR USAGE\n ./main <tasks_file> <mode> <wait>\n");
		return 0;
	}

	strcpy(tasks_file, argv[1]);
	strcpy(mode, argv[2]);
	wait = atoi(argv[3]);


	if(!strcmp(mode,VERIF)) {

		input_tasks(tasks_file);
		init_tree();

		input_certif();

		display_certif();

		if(check_certif())
			cout << "CERTIF OK !" << endl;
		else
			cout << "CERTIF KO :(" << endl;

	}
	else if (!strcmp(mode,NONDET)) {

		input_tasks(tasks_file);
		init_tree();

		gen_random_certif();
		display_certif();

		if(check_certif())
			cout << "CERTIF OK !" << endl;
		else
			cout << "CERTIF KO :(" << endl;
	}
	else if (!strcmp(mode,EXHAUST)) {

		input_tasks(tasks_file);
		init_tree();
		BritishMuseum(wait);
	}
	else if (!strcmp(mode,PART)) {

		input_part(tasks_file);
		display_tasks();
		display_matrix();
		init_tree();

		BritishMuseum(wait);
	}
	else
		printf("[ERROR] INVALID MODE !! \n");


	return 0;
}
