#!/bin/bash

echo "===================="
echo "Calculatrice normale"
echo "===================="

echo "Compilation ...."
make calcul

echo "Test ...."
# +
echo "echo '1 + 2' > input"
echo "1 + 2" > input
echo "./calcul < input"
./calcul < input

# -
echo "echo '1 - 2' > input"
echo "1 - 2" > input
echo "./calcul < input"
./calcul < input

# *
echo "echo '1 * 2' > input"
echo "1 * 2" > input
echo "./calcul < input"
./calcul < input

# /
echo "echo '4 / 2' > input"
echo "4 / 2" > input
echo "./calcul < input"
./calcul < input

echo "==============================="
echo "Calculatrice notation polonaise"
echo "==============================="

echo "Compilation ...."
make pol_calcul

echo "Test ...."
# +
echo "echo '1 2 +' > input"
echo "1 2 +" > input
echo "./pol_calcul < input"
./pol_calcul < input

# -
echo "echo '1 - 2' > input"
echo "1 2 -" > input
echo "./pol_calcul < input"
./pol_calcul < input

# *
echo "echo '1 * 2' > input"
echo "1 2 *" > input
echo "./pol_calcul < input"
./pol_calcul < input

# /
echo "echo '4 2 /' > input"
echo "4 / 2" > input
echo "./pol_calcul < input"
./pol_calcul < input

# MIX
echo "echo '1 1 - 4 + 2 / * 7' > input"
echo "1 1 - 4 + 2 / * 7" > input
echo "./pol_calcul < input"
./pol_calcul < input


echo "Cleaning ...."
read -p "Voulez vous supprimer le fichier input ? (Y/N)" ok
if [ "$ok" == 'y' ] || [ "$ok" == 'Y' ]
then
	rm input
	echo "Supression réussie"
else
	echo "Supression annulée"
fi

read -p "make clean ?" ok
if [ "$ok" == 'y' ] || [ "$ok" == 'Y' ]
then
	make clean
	echo "..... Done"
else
	echo "..... Stop"
fi


exit 0