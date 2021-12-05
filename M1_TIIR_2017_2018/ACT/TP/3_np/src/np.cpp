#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include "matrix_quicksort.h"
#include "utils.h"

using namespace std;

int task_of_machine_buff[MAX_TASKS][2];

int get_tasks_of_m (int machine) {

	int j = 0;

	for (int i = 0; i < nb_t; i++) {

		if (certif[i][1] == machine) {

			task_of_machine_buff[j][0] = certif[i][0];
			task_of_machine_buff[j++][1] = i;
		}
	}

	return j;
}

int check_certif () {

	int d_i, a_i;
	int nb_tasks_for_m;

	/* check arrivals time */
	for (int i = 0; i < nb_t; i++) {

		a_i = tasks[i];
		d_i = certif[i][0];

		if ((d_i - a_i > d) || (d_i < a_i)) {

			printf("error_certif: arrivals time || (d_i - a_i > d) || (d_i < a_i)\n");
			printf(" d_i= %d, a_i = %d, d = %d\n",d_i, a_i, d);

			return 0;
		}
	}

	/* check for start time of every task for each machine */
	int t_i, d_i_plus_1;

	for (int i = 0; i < nb_m; i++) {

		nb_tasks_for_m = get_tasks_of_m(i);    /* split matrix with machines */

		quickSort(task_of_machine_buff, 0, nb_tasks_for_m - 1);

		for (int k = 0; k < nb_tasks_for_m - 1; k++) {

			d_i = task_of_machine_buff[k][0];

			t_i = tasks[task_of_machine_buff[k][1]];

			d_i_plus_1 = task_of_machine_buff[k + 1][0];

			if (d_i + t_i > d_i_plus_1) {

				/*cout << "error_certif: d_i + t_i > d_i_plus_1" << endl;
				cout << "nb_tasks_for_m = " << nb_tasks_for_m << ", task_of_machine_buff = ";

				for (int j = 0; j < nb_tasks_for_m; j++)
					cout << task_of_machine_buff[j][0] << "\t";

				cout << endl << "task num " << k << endl;
				cout << "d_i= " << d_i << ", d_i_plus_un=" << d_i_plus_1 << ", t_i= " << t_i << ", a_i= " << a_i << ", d= " << d << endl;*/

				return 0;
			}
		}
	}

	return 1;
}

void gen_random_certif () {

	int d_i, m_i;

	for (int i = 0; i < nb_t; i++) {

		m_i = rand() % nb_m;
		d_i = (rand() %  d) + tasks[i];

		certif[i][0] = d_i;
		certif[i][1] = m_i;
	}

	return;
}
