#!/usr/bin/env bash

echo ""
echo "================="
echo "Testing bloc.o ..."
echo "================="
echo ""

echo "=== creating the disk ==="
echo -n " making the disk ..."
../build/bin/mkhd
echo " DONE !"
echo ""

echo "=== formatting the disk ==="
echo -n " formatting all the disk ..."
../build/bin/frmt -a
echo " DONE !"
echo ""

echo "=== create new volumes ==="
echo " create new vol; sec=0, cyl=1, blocs=10"
../build/bin/mkvol -s 1 -c 0 -b 10
echo ""
echo " create new vol; sec=5, cyl=0, blocs=15"
../build/bin/mkvol -s 12 -c 0 -b 15
echo ""
echo " create new vol; sec=10, cyl=0, blocs=20"
../build/bin/mkvol -s 10 -c 10 -b 20
echo ""

echo "=== making new file system ==="
echo -n " mknfs -v 0 -s 0 -n vol0"
../build/bin/mknfs -v 0 -s 7700 -n VOL_0
echo " ... DONE !"
echo -n " mknfs -v 1 -s 1 -n vol1"
../build/bin/mknfs -v 1 -s 7711 -n VOL_1
echo " ... DONE !"
echo -n " mknfs -v 2 -s 2 -n vol2"
../build/bin/mknfs -v 2 -s 7722 -n VOL_2
echo " ... DONE !"

echo "=== listing volumes ==="
echo " listing volumes : "
../build/bin/dvol -a
echo ""

echo "=== displaying file system ==="
echo "dfs -a"
../build/bin/dfs -a
echo ""

echo "=== testing allocation blocs ==="
echo "nbloc -v 0 -n 5"
../build/bin/nbloc -v 0 -n 10
echo "nbloc -v 1 -n 14"
../build/bin/nbloc -v 1 -n 14
echo ""
echo "nbloc -v 2 -n 15"
../build/bin/nbloc -v 2 -n 15
echo ""

echo "=== displaying file system ==="
echo "dfs -a"
../build/bin/dfs -a

echo "=== testing delete blocs ==="
echo "dbloc -v 0 -n 5"
../build/bin/dbloc -v 0 -n 5
echo "dbloc -v 1 -n 10"
../build/bin/dbloc -v 1 -n 10
echo "dbloc -v 2 -n 10"
../build/bin/dbloc -v 2 -n 10
echo ""

echo "=== displaying file system ==="
echo "dfs -a"
../build/bin/dfs -a