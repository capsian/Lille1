#!/bin/bash

echo "Création fichier test_mtail.txt"
touch test_mtail.txt
echo "echo \"ligne1\n\n\nligne2\nligne3\n.....\nligne15\" >> test_mtail.txt"
echo -e "ligne1\n\n\nligne2\nligne3\nligne4\nligne5\nligne6\nligne7\nligne8\nligne9\nligne10\nligne11\nligne12\nligne13\nligne14\nligne15" >> test_mtail.txt
echo "tail test_mtail.txt : (Appuyez)"
read
tail test_mtail.txt
echo ""
echo "============="
echo "mtail_stupide"
echo "============="
echo ""
echo "./mtail_stupide test_mtail.txt"
read
./mtail_stupide test_mtail.txt
echo ""
echo "./mtail_stupide test_mtail.txt 5"
read
./mtail_stupide test_mtail.txt 5
echo ""
echo ""
echo "./mtail_stupide test_mtail.txt 17"
read
./mtail_stupide test_mtail.txt 15
echo ""
echo "./mtail_stupide test_mtail.txt 100"
read
./mtail_stupide test_mtail.txt 100
echo ""
echo "============="
echo "mtail"
echo "============="
echo "./mtail test_mtail.txt [!] ERREUR AFFICHAGE [DEPASSEMENT TAILLE TAMPON] : (Appuyez)"
read
./mtail test_mtail.txt
echo ""
echo "./mtail test_mtail.txt 5 [!] ERREUR AFFICHAGE [DEPASSEMENT TAILLE TAMPON] : (Appuyez)"
read
./mtail test_mtail.txt 5
echo ""
echo "./mtail test_mtail.txt 8 : (Appuyez)"
read
./mtail test_mtail.txt 8
echo ""
echo "./mtail test_mtail.txt 13 [!] ERREUR LSEEK [DEPASSEMENT TAILLE TAMPON]  : (Appuyez)"
read
./mtail test_mtail.txt 13
echo ""
echo "./mtail test_mtail.txt 18 [!] ERREUR LSEEK [DEPASSEMENT TAILLE FICHIER] : (Appuyez)"
read
./mtail test_mtail.txt 18
echo ""
echo "./mtail test_mtail.txt 20 [!] ERREUR LSEEK [DEPASSEMENT TAILLE FICHIER] : (Appuyez)"
read
./mtail test_mtail.txt 20
echo ""
read -p "Voulez vous supprimer le fichier test_mtail.txt créer ? (Y/N)" ok
if [ "$ok" == 'y' ] || [ "$ok" == 'Y' ]
then
	rm test_*
	echo " Supression réussie"
else
	echo " Supression annulée"
fi

exit 0
