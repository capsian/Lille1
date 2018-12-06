# ASE -  TP5 : Un système de fichier à la Unix
## Groupe 5
 * Dambrine Valentin <valentin.dambrine@etudiant.univ-lille1.fr>
 * Lakhdar Selim <selim.lakhdar@etudiant.univ-lille1.fr>

## Structure du rendu

 * `Makefile` : Makefile pour la compilation du TP ;
 * `README.md` : Fichier expliquant le rendu, l'aboutissement du travail accompli, et la façon dont tester le code source contenu dans le dossier ;
 * `etc` : Répertoire contenant le fichier `hardware.ini` nécessaire à l'initialisation du matériel ;
 * `include` : Répertoire contenant les différents headers du projet ;
 * `src` : Répertoire contenant les sources du projets.  

## Rendu

#### I. Première couche logicielle : accès au matériel 

##### - drive.o

- Compilation & test  
`make test_drive`


#### II. Seconde couche logicielle : gestion de volumes

##### - mbr.o && vol.o

- Compilation & test  
`make test_mbr`


#### III. Troisième couche logicielle, 1re partie : structure d'un volume (super bloc)
#### IV. Troisième couche logicielle, 2e partie : structure d'un fichier

##### - bloc.o

- Compilation & test   
`make test_bloc`

#### V. Quatrième couche logicielle : manipulation de fichiers

##### - ifile

- Compilation & test   
`make test_ifile`

