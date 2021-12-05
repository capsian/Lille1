#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>

#include "graphe.h"

typedef enum {ROUGE=0, BLEU=1, VERT=2} tCouleur;
typedef tCouleur tTabCouleurs[MAX_SOMMETS];

static int nb_s = 0;
static tCouleur r = 0;
static tCouleur b = 1;
static tCouleur v = 2;
tTabCouleurs tab;

typedef struct node node;
struct node
{
	tNomSommet nom;
	node* next;
};

node* add_end(node* h, tNomSommet s)
{
	node* new = malloc(sizeof(node));
	strcpy(new->nom,s);
	new->next = NULL;

	node* tmp = h;

	while (tmp->next != NULL)
		tmp = tmp->next;

	tmp->next = new;

	return h;
}

node* mystere(tGraphe graphe)
{
	tFileSommets file = fileSommetsAlloue();
	node* liste = malloc(sizeof(node) * 5);
	int i;
	tNumeroSommet x,y;

	for (i=0;i<nb_s;i++)
	{
		if (grapheNbPredecesseursSommet(graphe, i) != 0)
			tab[i] = b;
		else
		{
			tab[i] = v;
			fileSommetsEnfile (file, i);
		}
	}

	while (!fileSommetsEstVide(file))
	{
		x  = fileSommetsDefile(file);
	} 

	return NULL;
}

/* remplir le tableau de couleur en bleu sauf pour le sommet exculded */
void colorate_expected(tNumeroSommet exculded)
{
	int i;
	
	for (i=0;i<nb_s;i++)
		if (i != exculded)
			tab[i] = b;
}

/* remplir le tableau de couleur avec color */
void colorate_all_in(int color)
{
	int i;
	
	for (i=0;i<nb_s;i++)
			tab[i] = color;
}

/* init le tableau avec init */
void init_tab_with(tNumeroSommet* tab, int init)
{	
	int i;
	for (i=0;i<nb_s;i++)
		*(tab+i) = init;
		
	return;
}

/** affiche le tableau suivant nom
*si nom == 0 : affiche les num des sommets
*sinon       : affiche les noms des sommets
*/
void display(tGraphe graphe, tNumeroSommet* tab, int nom)
{
	int i;
	//affiche num sommet
	if (nom == 0)
		for (i=0;i<nb_s;i++)
			printf("%d\t",*(tab+i));
	else
	{
		//affiche nom
		tNomSommet tmp;
		for (i=0;i<nb_s;i++)
		{
			grapheRecupNomSommet(graphe,*(tab+i),tmp);
			printf("%s\t",tmp);
		}
	}
	printf("\n");
	return;
}

void shortest(tGraphe graph, tNomSommet s)
{
	tFileSommets file = fileSommetsAlloue();
	tNumeroSommet x,y;
	tNumeroSommet i;
	/* init à 0 */
	int* d = malloc(sizeof(int) * nb_s);
	tNumeroSommet* pred = malloc(sizeof(tNumeroSommet) * nb_s);
	init_tab_with(d,0);
	init_tab_with(pred,0);
	
	// tous colorier en bleu sauf s
	colorate_expected(grapheChercheSommetParNom(graph,s));
	
	// colorier s en vert & l'enfiler
	tab[grapheChercheSommetParNom(graph,s)] = v;
	fileSommetsEnfile (file, grapheChercheSommetParNom(graph,s));
	
	while (!fileSommetsEstVide(file))
	{
		x  = fileSommetsDefile(file);
		
		// les voisins
		for (i=0; i<grapheNbVoisinsSommet(graph,x); i++)
		{
			// pour tout voisin y de x
			y = grapheVoisinSommetNumero(graph,x,i);
			
			// voisin bleu
			if ( tab[y] == b)
			{
				// colorier y en vert & enfiler
				tab[y] = v;
				fileSommetsEnfile (file,y);
				
				// calculer d(y) & pred(y)
				d[y] = d[x] + 1;
				pred[y] = x;
			}
		}
		// colorier x en rouge
		tab[x] = r;
	}
	
	display(graph,d,0);
	display(graph,pred,1);
	
	free(file);
	return;
}

/* retourne le num d'un sommet bleu, -1 sinon */
int sommet_bleu_alea(tTabCouleurs tab, int n)
{
	int i;
	tCouleur b = 1;
	
	for (i=0; i<n; i++)
	{
		if (tab[i] == b)
			return i;
	}
	return -1;
}

tNumeroSommet* topo (tGraphe graphe)
{
	tPileSommets pile = pileSommetsAlloue();
	tNumeroSommet x,y;
	int i,nb_succ,check_blue=-1;
	
	int existe_sommet_bleu,w = nb_s - 1;
	tNumeroSommet* result = malloc(sizeof(tNumeroSommet) * nb_s);
	
	/* tout colorier en bleu */
	colorate_all_in(b);
	
	/* tq il existe un sommet bleu */
	while ((existe_sommet_bleu = sommet_bleu_alea(tab,nb_s)) != -1)
	{
		/* colorier le sommet en v & empiler */
		tab[existe_sommet_bleu] = v;
		pileSommetsEmpile(pile, existe_sommet_bleu);
		
		while (!pileSommetsEstVide(pile))
		{
			/* x = sommetPile & recup nb_successeur ( graph orienté) */
			x = pileSommetsTete(pile);
			nb_succ = grapheNbSuccesseursSommet (graphe,x);
			
			/* recherche d'un sommet succ bleu, le colorier en vert & l'empiler */
			for (i=0; i<nb_succ; i++)
			{
				y = grapheSuccesseurSommetNumero(graphe,x,i);

				if (tab[y] == b)
				{
					tab[y] = v;
					check_blue = y;
					break;
				}
			}
			/* empiler le sommet trouvé */
			if (check_blue != -1)
				pileSommetsEmpile(pile, check_blue);
			else
			{
				/* si on ne trouve pas de sommet */
				tab[x] = r;
				y = pileSommetsDepile(pile);
				result[w] = y;
				w--;
			}
			/* re-init check_blue  */
			check_blue = -1;
		}
	}
	
	return result;
}

tNumeroSommet* profondeur(tGraphe graphe, tNomSommet s)
{
	tNumeroSommet* result = malloc(sizeof(tNumeroSommet) * nb_s);
	tPileSommets pile = pileSommetsAlloue();
	tNumeroSommet x,y;
	int i,w=0;
	int nb_succ,check_blue=-1;
	
	
	/* colorier */
	colorate_expected(grapheChercheSommetParNom(graphe,s));
	/* colorier s en vert & empiler */
	tab[grapheChercheSommetParNom(graphe,s)] = v;
	pileSommetsEmpile(pile, grapheChercheSommetParNom(graphe,s));
	
	while (!pileSommetsEstVide(pile))
	{
		x = pileSommetsTete(pile);
		nb_succ = grapheNbSuccesseursSommet (graphe,x);
		
		/* recherche d'un sommet succ bleu, le colorier en vert & l'empiler */
		for (i=0; i<nb_succ; i++)
		{
			y = grapheSuccesseurSommetNumero(graphe,x,i);

			if (tab[y] == b)
			{
				tab[y] = v;
				check_blue = y;
				break;
			}
		}
		/* empiler le sommet trouvé */
		if (check_blue != -1)
			pileSommetsEmpile(pile, check_blue);
		else
		{
			/* si on ne trouve pas de sommet */
			tab[x] = r;
			y = pileSommetsDepile(pile);
			result[w] = y;
			w++;
		}
		/* re-init check_blue  */
		check_blue = -1;
	}
	
	return result;
}


tNumeroSommet* largeur(tGraphe graphe, tNomSommet s)
{
	tNumeroSommet* result = malloc(sizeof(tNumeroSommet) * nb_s);
	tFileSommets file = fileSommetsAlloue();
	tNumeroSommet x,y;
	int i,w=0;
	
	
	/* colorier */
	colorate_expected(grapheChercheSommetParNom(graphe,s));
	/* colorier s en vert & enfiler */
	tab[grapheChercheSommetParNom(graphe,s)] = v;
	fileSommetsEnfile (file, grapheChercheSommetParNom(graphe,s));
	
	while (!fileSommetsEstVide(file))
	{
		x  = fileSommetsDefile(file);
		
		// les voisins
		for (i=0; i<grapheNbVoisinsSommet(graphe,x); i++)
		{
			// pour tout voisin y de x
			y = grapheVoisinSommetNumero(graphe,x,i);
			
			// voisin bleu
			if ( tab[y] == b)
			{
				// colorier y en vert & enfiler
				tab[y] = v;
				fileSommetsEnfile (file,y);
			}
		}
		result[w] = x;
		w++;
	}
	
	return result;
}





int main(int argc, char **argv)
{
	if (argc<3) 
    halt("Usage : %s FichierGraphe SommetDepart\n", argv[0]);
  tGraphe graph;
  tNomSommet sommet;
  
  graph = grapheAlloue();
  grapheChargeFichier(graph, argv[1]);
  strcpy(sommet,argv[2]);
  
  nb_s = grapheNbSommets(graph);
  
  tNumeroSommet* result = profondeur(graph,sommet);
  
  display(graph,result,1);
  
  free(graph);
	exit(EXIT_SUCCESS);
}
