#ifndef TP_TREE_H
#define TP_TREE_H

/*
 *    http://www.fil.univ-lille1.fr/~lemairef/ARO//doclibgraphe/index.html
 */

#define MAX_SOMMETS 11500
#define MAX_ARCS (10000000) /* 10M :o */
#define LONG_NOM_SOMMET_MAX 50
typedef char tNomSommet[LONG_NOM_SOMMET_MAX];
typedef int tNumeroSommet;
typedef double tValeurArc;
typedef enum {ROUGE=0, BLEU=1, VERT=2} tCouleur;
typedef tCouleur tTabCouleurs[MAX_SOMMETS];

typedef struct  {
	int tab[MAX_SOMMETS];
	int nb;
} tTableauEntiers;

typedef struct  {
	int orig;
	int dest;
	tValeurArc val;
} tArc;

typedef struct  {
	tArc tab[MAX_ARCS];
	int nb;
} tTableauArcs;

typedef struct tGraphe1{
	int estOriente;

	int nbSommets;
	tNomSommet nomSommets[MAX_SOMMETS];
	
	tValeurArc matriceAdjacence[MAX_SOMMETS][MAX_SOMMETS];
	tTableauEntiers tableSuccesseurs[MAX_SOMMETS];
	tTableauEntiers tablePredecesseurs[MAX_SOMMETS];
	tTableauEntiers tableVoisins[MAX_SOMMETS];
	tTableauArcs tableArcs;

} *tGraphe;

typedef struct tFileSommets1 {
	tNumeroSommet tab[MAX_SOMMETS+1];

	int debut;
	int fin;
	
} *tFileSommets;


typedef struct tPileSommets1 {
	
	tNumeroSommet tab[MAX_SOMMETS];
	int tete;
} *tPileSommets;

extern "C" tGraphe grapheAlloue();
extern "C" int grapheNbSommets(tGraphe graphe);
extern "C" int grapheChargeFichier(tGraphe graphe, const char *fichier);
extern "C" int grapheNbVoisinsSommet(tGraphe graphe, int sommet);
extern "C" void grapheLibere(tGraphe graphe);
extern "C" tNumeroSommet grapheChercheSommetParNom(tGraphe graphe, tNomSommet nomSommet);
extern "C" tPileSommets pileSommetsAlloue();
extern "C" void pileSommetsEmpile(tPileSommets, tNumeroSommet);
extern "C" int pileSommetsEstVide(tPileSommets);
extern "C" tNumeroSommet pileSommetsTete(tPileSommets);
extern "C" tNumeroSommet grapheVoisinSommetNumero(tGraphe graphe, tNumeroSommet sommet, int i);
extern "C" tNumeroSommet pileSommetsDepile(tPileSommets);
extern "C" void grapheRecupNomSommet(tGraphe graphe, tNumeroSommet numero,tNomSommet nomSommet);
extern "C" void pileSommetsLibere(tPileSommets);
extern "C" int grapheNbArcs(tGraphe graphe);
extern "C" int grapheNbSuccesseursSommet(tGraphe graphe, tNumeroSommet sommet);
extern "C" tNumeroSommet grapheVoisinSommetNumero(tGraphe graphe,tNumeroSommet sommet,int i);
extern "C" int grapheNbSuccesseursSommet(tGraphe graphe, tNumeroSommet sommet);
extern "C" tNumeroSommet grapheSuccesseurSommetNumero(tGraphe graphe,tNumeroSommet sommet,int i);



#define TREE_NAME   "out.grp"

extern int nb_nodes;
extern int nb_certif;

extern tGraphe graphe;

void make_file();
void init_tree();

void construct_tree(const char* filename);
void connect(int i, int from, int to);
void write_header();
void write_tops();
void write_arrows();

void get_certif_n (tGraphe graphe, int n);
int extract_top_name(tNomSommet nom);
tPileSommets parcours_graphe(tGraphe graphe, int n);


#endif
