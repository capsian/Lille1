#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <sstream>

#include "tree.h"
#include "utils.h"

using namespace std;

int nb_nodes;
int nb_certif = 0;

string nodes[1000];

FILE* out;

void init_tree() {

	construct_tree(TREE_NAME);
	graphe = grapheAlloue();
	grapheChargeFichier(graphe,TREE_NAME);
}

void construct_tree(const char* filename) {

	out = fopen (filename,"w");

	write_header();
	write_tops();
	write_arrows();

	fclose(out);
}

void write_header() {

	fprintf (out, "# type\n");
	fprintf (out, "type = oriente;\n\n");
	fprintf (out, "# la liste des sommets\n");
	fprintf (out, "sommets = ");
}

void write_tops() {

	int tmp_d = 0;
	int tmp_m = 0;
	int t_i   = 0;

	nb_nodes = ((d+1)*nb_t) + (nb_m*nb_t) + 1;
	char tmp_buff[10];
	nodes[0].clear();
	nodes[0].append("r_0_0");
	fprintf (out, "r_0_0 ");
	/* tasks */

	for (int i = 1; i < nb_nodes - (nb_m*nb_t); i++) {

		if (tmp_d > d) {
			tmp_d = 0;
			t_i++;
		}

		fprintf (out, "t_%d_%d ",t_i,tasks[t_i] + tmp_d++);

		nodes[i].clear();
		nodes[i].append("t_");

		sprintf(tmp_buff,"%d",t_i);
		nodes[i].append(tmp_buff);
		nodes[i].append("_");

		sprintf(tmp_buff,"%d",tasks[t_i] + tmp_d-1);
		nodes[i].append(tmp_buff);
	}

	/* machines */
	t_i = 0;
	for (int i = nb_nodes - (nb_m*nb_t); i < nb_nodes; i++) {

		if (tmp_m == nb_m) {
			tmp_m = 0;
			t_i++;
		}

		fprintf (out, "m_%d_%d ",t_i,tmp_m++);

		nodes[i].clear();
		nodes[i].append("m_");

		sprintf(tmp_buff,"%d",t_i);
		nodes[i].append(tmp_buff);
		nodes[i].append("_");

		sprintf(tmp_buff,"%d",tmp_m - 1);
		nodes[i].append(tmp_buff);
	}

	fprintf (out, ";\n\n");

}

void write_arrows() {

	int from = d+1;
	int to   = d+d+1;
	int cpt = 0;

	fprintf (out, "# la liste des arcs\n");
	fprintf (out, "arcs = \n");

	connect(0,1,d+1);

	/* connect tasks */
/*
	cout << " ***** TASKS ******" << endl;
*/
	for (int i = 1; i <= (nb_t-1)*(d+1); i++) {

		if (cpt > d)
			cpt = 0;

		from = i + d + 1 - cpt;
		to = from + d;
		cpt++;

		connect(i,from,to);
	}

/*
	cout << " ***** BETWEEN ******" << endl;
*/

	/* connect last tasks with machines */
	from = (nb_t)*(d+1)+1;
	to = from + nb_m - 1 ;
	for (int i = 0; i <= d; i++) /* < nb_t */
		connect(i+(nb_t-1)*(d+1)+1,from,to);

	cpt = 0;
	from = nb_t*(d+1) + nb_m ;
	to = from + nb_m - 1;

/*
	cout << " ***** MACHINES ******" << endl;
*/

	/* connect machines */
	for (int i = nb_t*(d+1)+1; i < nb_nodes - nb_m; i++) {

		if (cpt >= nb_m)
			cpt = 0;

		from = i + nb_m - cpt;
		to = from + nb_m -1;
		connect(i,from,to);
		cpt++;
	}

	fprintf (out, ";");
}

void connect(int i, int from, int to) {

	string source,dest;

	source.assign(nodes[i]);

/*
	cout << " connect " << i << " : " << from << " ==> " << to << endl;
*/

	for (int j = from; j <= to; j++) {

		dest.assign(nodes[j]);
		fprintf (out, "%s  %s %d\n", source.data(), dest.data(), 1);
	}
}

tPileSommets parcours_graphe(tGraphe graphe, int n) {

	tCouleur color[grapheNbSommets(graphe)] = {VERT};
	tNumeroSommet sommet_depart = 0, sommet_courant = 0, tmp_top_num;
	tPileSommets pile;
	int l, found = 0, num_certif =0;

	pile = pileSommetsAlloue();
	pileSommetsEmpile(pile,sommet_courant);

	//On cherche le successeur qui n'est pas BLEU
	while (color[sommet_depart] != BLEU) {

		sommet_courant = pileSommetsTete(pile);

		if (grapheNbSuccesseursSommet(graphe,sommet_courant) == 0) {

			if(num_certif == n )
				return pile;
			else {

				num_certif++;
				color[sommet_courant] = BLEU;
				pileSommetsDepile(pile); //Reprendre le pred
			}
		}

		found = 0; /* try to comment ??? */

		/* select a neighbour */
		for(l = 0; l < grapheNbSuccesseursSommet(graphe,sommet_courant);l++) {

			tmp_top_num = grapheSuccesseurSommetNumero(graphe,sommet_courant,l);

			if (color[tmp_top_num] != BLEU) {

				pileSommetsEmpile(pile,tmp_top_num);
				found = 1;
				break;
			}
		}

		if(!found) {

			color[sommet_courant] = BLEU;

			for(l = 0; l < grapheNbSuccesseursSommet(graphe,sommet_courant);l++){

				tmp_top_num = grapheSuccesseurSommetNumero(graphe,sommet_courant,l);
				color[tmp_top_num] = VERT;
			}

			pileSommetsDepile(pile); //Reprendre le pred
		}
	}

	return pile;
}

int extract_top_name(tNomSommet nom) {

	string line,result;
	stringstream  data(nom);

	while (getline(data,line,'_'))
		result = line;

	return stoi(result, NULL, 10);
}

void get_certif_n (tGraphe graphe, int n) {

	int i, tmp_top_name;
	tNomSommet res[nb_t + nb_t];

	tPileSommets ret = parcours_graphe(graphe,n);

	for(i = nb_t *2 -1; i >= 0 ; i--)
		grapheRecupNomSommet(graphe,pileSommetsDepile(ret),res[i]);

	/* fill tasks for certif */
	for(i = 0 ; i < nb_t ; i++) {

		tmp_top_name = extract_top_name(res[i]);
		certif[i][0] = tmp_top_name;
	}

	/* fill machines for certif */
	for(i = nb_t ; i < nb_t*2 ; i++) {

		tmp_top_name = extract_top_name(res[i]);
		certif[i - nb_t][1] = tmp_top_name;
	}
}
