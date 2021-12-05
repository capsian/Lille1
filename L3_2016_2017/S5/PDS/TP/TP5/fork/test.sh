#!/bin/bash

echo "== multif =="
echo "./multif 1 : (Appuyez)"
read
./multif 1
echo ""
echo "./multif 1 2 3 : (Appuyez)"
read
./multif 1 2 3
echo ""
echo "./multif 1 2 3 5 9 10 : (Appuyez)"
read
./multif 1 2 3 5 9 10

echo ""
echo "== race =="
echo "./race : (Appuyez)"
read
./race

echo ""
echo "== observation =="
echo "./observation (Appuyez)"
read
./observation

echo ""
read -p "make clean ? : (Y/N)" ok
if [ "$ok" == 'y' ] || [ "$ok" == 'Y' ]
then
	make clean
else
	echo " Supression annulée"
fi

exit 0
