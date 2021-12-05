#include <iostream>
#include <cstdlib>
#include <chrono>

#include "british_museum.h"
#include "utils.h"
#include "tree.h"
#include "np.h"

using namespace std;

void BritishMuseum(int wait) {

	nb_certif = 1;
	for (int i = 0; i < nb_t; i++) {
		nb_certif *= ((d+1)*nb_m);
	}

	int rand = std::rand() % nb_certif;

	for(auto runUntil = chrono::system_clock::now() + chrono::seconds(wait); chrono::system_clock::now() < runUntil;) {

		cout << "rand = " << rand << "/" << nb_certif << endl;
		get_certif_n(graphe, rand);
		
		if (!check_certif()) {

			cout << " CERTIF FOUND ! NUM = " << rand << "/" << nb_certif << endl;
			cout << "nb_t = " << nb_t << ", nb_m = " << nb_m << ", d = " << d << endl;
			display_certif();

			return;
		}

		rand = std::rand() % nb_certif;
	}

	cout << "NO VALID CERTIF FOUND !! tested : " << rand << "/" << nb_certif  << endl;

	return;
}
