#!/bin/bash

#777
echo "========== Test 1 =========="
echo "Création fichier test_maccess_777 avec chmod 777 || ./maccess test_maccess_777 -r -x -w -v"
touch test_maccess_777
chmod 777 test_maccess_777
./maccess test_maccess_777 -r -x -w -v
echo "==========================="

#000
echo "========== Test 2 =========="
echo "Création fichier test_maccess_000 avec chmod 000 || ./maccess test_maccess_000 -r -x -w -v"
touch test_maccess_000
chmod 000 test_maccess_000
./maccess test_maccess_000 -r -x -w -v
echo "==========================="

#111
echo "========== Test 3 =========="
echo "Création fichier test_maccess_111 avec chmod 111 || ./maccess test_maccess_111 -r -x -w -v"
touch test_maccess_111
chmod 111 test_maccess_111
./maccess test_maccess_111 -r -x -w -v
echo "==========================="

#222
echo "========== Test 4 =========="
echo "Création fichier test_maccess_222 avec chmod 222 || ./maccess test_maccess_222 -r -x -w -v"
touch test_maccess_222
chmod 222 test_maccess_222
./maccess test_maccess_222 -r -x -w -v
echo "==========================="

#444
echo "========== Test 5 =========="
echo "Création fichier test_maccess_444 avec chmod 444 || ./maccess test_maccess_444 -r -x -w -v"
touch test_maccess_444
chmod 444 test_maccess_444
./maccess test_maccess_444 -r -x -w -v
echo "==========================="

#invalid arg
echo "========== Test 6 =========="
echo "Utilisation de la commande sans arg  (implémentation de la valeur de retour) || ./maccess"
./maccess
echo "Utilisation de la commande sans parametres  (implémentation de la valeur de retour) || ./maccess test_maccess_007"
./maccess test_maccess_007
echo "==========================="

#symb_link
echo "========== Test 7 =========="
echo "Création du lien symb qui renvoi vers maccess.c (boucle) || ln -s ./link ./link"
ln -s ./link ./link
echo "Utilisation de la commande sur un ln (boucle) || ./maccess ./link -r -w -x"
./maccess ./link -r -w -x
echo "==========================="

#not_file
echo "========== Test 8 =========="
echo "Utilisation de la commande sur un fichier inexsistant || ./maccess aaaazzzz -r -w -x"
./maccess aaaazzzz -r -w -x
echo "==========================="

#not_dir
echo "========== Test 9 =========="
echo "Utilisation de la commande sur un dossier inexsistant || ./maccess maccess.c/test -r -w -x"
./maccess maccess.c/test -r -w -x
echo "==========================="

#other
echo "Les autres erreurs possibles"
echo "EROFS : Ecriture sur un système de fichiers en lecture seule."
echo "EFAULT : Débordement de pathname."
echo "EIO : Erreur entrée/sortie."
echo "ENOMEM : Insuffisance mémoire."
echo "ETXTBSY : Ecriture dans un fichier exécutable en cours d'utilisation." 

#clean
echo ""
echo "##########################"
read -p "Supprimer les fichiers tests crées ? (y/n) : " ok
if [ "$ok" == 'y' ] || [ "$ok" == 'Y' ]
then
	rm test_* link
	echo "Supression réussie"
else
	echo "Supression annulée"
fi






