# ASE - TP 1.3
## Groupe 5
 * Dambrine Valentin <valentin.dambrine@etudiant.univ-lille1.fr>
 * Lakhdar Selim <selim.lakhdar@etudiant.univ-lille1.fr>

## Structure du rendu

 * `Makefile` : Makefile pour la compilation du TP ;
 * `README.md` : Fichier expliquant le rendu, l'aboutissement du travail accompli, et la façon dont tester le code source contenu dans le dossier ;
 * `etc` : Répertoire contenant le fichier `hardware.ini` nécessaire à l'initialisation du matériel ;
 * `include` : Répertoire contenant les différents headers du projet ;
 * `tmr.c` : Code source pour gérer les interruptions ;
 * `yield.c` : Programme permettant d'illustrer le changement de contexte avec un ordonnancement sur interruptions.

## Rendu

Tous les programmes sont fonctionnels.

### Compilation

`yield` : `make`  
  
### Exécution

Veuillez à avoir les droits d'exécution pour le fichier `yield`.   
  
`./yield` lance le programme dans la console.

### Nettoyage

`make clean` nettoyera les fichiers exécutables et binaires.