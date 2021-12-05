#include "graphToVisu.h"
#include "sys/wait.h"
#include "graphe.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
/* N´ecessaire pour la macro WEXITSTATUS */
void graphe2visu(tGraphe graphe, char *outfile) {
  tNomSommet nom;
  tArc arc;
  tNumeroSommet i;
  FILE *fic;
  char commande[80];
  char dotfile[80]; /* le fichier dot pour cr´eer le ps */
  int ret;
  /* on va cr´eer un fichier pour graphviz, dans le fichier "outfile".dot */
  strcpy(dotfile, outfile);
  strcat(dotfile, ".dot");
  fic = fopen(dotfile, "w");
  if (fic==NULL)
    halt ("Ouverture du fichier %s en ´ecriture impossible\n", dotfile);
  /*
  on parcourt le graphe pour en tirer les informations
  n´ecessaires pour graphviz.
  Pour ´ecrire dans le fichier, on utilise fprintf (qui s’utilise
  comme printf mais on mettant en plus fic comme premier param`etre).
  Ex :
  fprintf(fic, "graph {\n");
  ou
  fprintf(fic, " %s -> %s\n", origine, destination);
  */
  if (grapheEstOriente(graphe)){
    fprintf(fic,"digraph {\n");
  } else{
    fprintf(fic,"graph {\n");
  }
  for(i=0; i < grapheNbArcs(graphe); i++) {
    arc = grapheRecupArcNumero(graphe, i);
    grapheRecupNomSommet(graphe, arc.orig, nom);
    fprintf(fic,"  %s", nom);
    if (grapheEstOriente(graphe)) {
      fprintf(fic," -> ");
    } else {
      fprintf(fic," -- ");
    }
    grapheRecupNomSommet(graphe, arc.dest, nom);
    fprintf(fic,"%s\n",nom);
  }
  fprintf(fic,"}\n");
  fclose(fic) ;
  sprintf(commande, "dot -Tps %s -o %s", dotfile, outfile);
  ret = system(commande);
  if (WEXITSTATUS(ret)) {
    halt("La commande suivante a echouée\n%s\n", commande);
  }
}


int main(int argc, char *argv[]) {

  tGraphe graphe;

  if (argc<3) {
    halt("Usage : %s FichierGraphe\n", argv[0]);
  }


  graphe = grapheAlloue();
  grapheChargeFichier(graphe,  argv[1]);
  graphe2visu(graphe,argv[2]);
  grapheLibere(graphe);
  exit(EXIT_SUCCESS);
}
