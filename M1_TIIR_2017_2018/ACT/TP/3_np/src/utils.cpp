#include <iostream>
#include <string.h>

#include "utils.h"

using namespace std;

int matrix[MAX_TASKS][2];
int certif[MAX_TASKS][2];
int tasks[MAX_TASKS];

int nb_m, nb_t, d;

void input_certif() {

	for (int i = 0; i < nb_t; i++)
		cin >> certif[i][0] >> certif[i][1];

	return;
}

void input_part(char* tasks_file) {

	int sum = 0;

	nb_m = 2;

	FILE* tmp_file = fopen (tasks_file,"r");

	fscanf(tmp_file,"%d\n",&nb_t);

	for (int i = 0; i < nb_t; i++) {

		fscanf(tmp_file,"%d\n",&matrix[i][1]);

		matrix[i][0] = 0;    /* RAND */

		tasks[i] = matrix[i][1];
		sum += matrix[i][1];
	}

	d = sum / 2;

	matrix[nb_t][0]   = 0;  matrix[nb_t][1]   = d;
	matrix[nb_t+1][0] = 0;  matrix[nb_t+1][1]   = d;

	tasks[nb_t] = d;
	tasks[nb_t+1] = d;

	nb_t += 2;

	fclose(tmp_file);
	return;

}



void input_tasks(char* tasks_file) {

	FILE* tmp_file = fopen (tasks_file,"r");

	fscanf(tmp_file,"%d\n%d\n",&nb_m, &nb_t);

	for (int i = 0; i < nb_t; i++) {

		fscanf(tmp_file,"%d %d\n",&matrix[i][0], &matrix[i][1]);

		tasks[i] = matrix[i][0];
	}

	fscanf(tmp_file,"%d\n",&d);

	fclose(tmp_file);
	return;
}

void display_matrix() {

	cout << " == Matrix == " << endl;

	for (int i = 0; i < nb_t; i++) {
		cout << matrix[i][0] << " \t " << matrix[i][1] << endl;
	}

	cout << endl;

	return;
}

void display_certif() {

	cout << " == Certif ==" << endl;

	for (int i = 0; i < nb_t; i++) {
		cout << certif[i][0] << " \t " << certif[i][1] << endl;
	}

	cout << endl;
	return;
}

void display_tasks() {

	cout << " == Tasks ==" << endl;

	for (int i = 0; i < nb_t; i++) {
		cout << tasks[i] << " | ";
	}

	cout << endl;
	return;
}
