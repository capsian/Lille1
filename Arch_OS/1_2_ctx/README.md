# ASE - TP 1.2
## Groupe 5
 * Dambrine Valentin <valentin.dambrine@etudiant.univ-lille1.fr>
 * Lakhdar Selim <selim.lakhdar@etudiant.univ-lille1.fr>

## Structure du rendu

 * `Makefile` : Makefile pour la compilation du TP ;
 * `README.md` : Fichier expliquant le rendu, l'aboutissement du travail accompli, et la façon dont tester le code source contenu dans le dossier ;
 * `ping_pong.c` : Programme illustrant un changement de contexte entre deux méthodes ;
 * `yield.c` : Programme illustrant un changement de contexte entre autant de contextes que souhaités ;
 * `yield.h` : Header du fichier `yield.c`.

## Rendu

Tous les programmes sont fonctionnels.

### Compilation

`ping_pong` : `make ping_pong`  
  
`yield` : `make `yield`  
  
### Exécution

Veuillez à avoir les droits d'exécution pour les fichiers `ping_pong` et `yield`.  
  
`./ping_pong` lance le programme dans la console, et peut être arrêté avec Ctrl+C pour constater l'alternance entre une lettre parmi {A,B,C} et un chiffre parmi {1,2}.  
`./yield` lance le programme dans la console, et affiche les caractères des chaînes de caractères contenues dans les contextes créés depuis le code source.

### Nettoyage

`make clean` nettoyera les fichiers exécutables et binaires.