# ASE - TP 1.1
## Groupe 5
 * Dambrine Valentin <valentin.dambrine@etudiant.univ-lille1.fr>
 * Lakhdar Selim <selim.lakhdar@etudiant.univ-lille1.fr>

## Structure du rendu

 * `Makefile` : Makefile pour la compilation du TP ;
 * `README.md` : Fichier expliquant le rendu, l'aboutissement du travail accompli, et la façon dont tester le code source contenu dans le dossier ;
 * `display_stack.c` : Code source pour l'affichage de la pile ;
 * `trace.log` : Résultat d'une trace d'affichage du programme __display_stack__ ;
 * `try.c` : Implémente les fonctions _try()_ et _throw()_, qui sauvegarde et restore un contexte ;
 * `try.h` : Header contenant la définiton d'un contexte ainsi que les prototypes des méthodes _try()_ et _throw()_ ;
 * `try_mul.c` : Donne un exemple d'utilisation de _try()_ et _throw()_ par une série de multiplications.

## Rendu

Tous les programmes sont fonctionnels.  

### Compilation

`display_stack` : `make display_stack`  
  
`try_mul` : `make try_mul`  
  
### Exécution

Veuillez à avoir les droits d'exécution pour les fichiers `display_stack` et `try_mul`.  

`./display_stack` lance le programme dans la console  
`./display_stack > trace.log` écrit la sortie du programme dans un fichier `trace.log`  
  
`./try_mul` lance le programme dans la console. Vous êtes alors invité à saisir une suite de nombres, séparé par un retour chariot, et en finissant votre suite par un signal EOF en appuyant sur Ctrl+D

### Nettoyage

`make clean` nettoyera les fichiers exécutables et binaires.