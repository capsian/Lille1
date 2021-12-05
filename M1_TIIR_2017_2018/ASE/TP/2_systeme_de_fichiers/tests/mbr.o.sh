#!/usr/bin/env bash

echo ""
echo "================="
echo "Testing mbr.o ..."
echo "================="
echo ""

echo "=== creating the disk ==="
echo -n " making the disk ..."
../build/bin/mkhd
echo " DONE !"
echo ""

echo "=== formating the disk ==="
echo -n " formating all the disk ..."
../build/bin/frmt -a
echo " DONE !"
echo ""

echo "=== listing volumes ==="
echo " listing volumes : "
../build/bin/dvol -a
echo ""

echo "=== create new volume ==="
echo " create new vol; sec=0, cyl=1, block=10"
../build/bin/mkvol -s 0 -c 1 -b 10
echo ""

echo "=== listing volumes ==="
echo " listing volumes :"
../build/bin/dvol -a
echo ""

echo "=== create new volume ==="
echo " create new vol; sec=5, cyl=0, block=15"
../build/bin/mkvol -s 5 -c 0 -b 15
echo ""

echo "=== listing volumes ==="
echo " listing volumes :"
../build/bin/dvol -a
echo ""

echo "=== create new volume ==="
echo " create new vol; sec=10, cyl=10, block=20"
../build/bin/mkvol -s 10 -c 10 -b 20
echo ""

echo "=== listing volumes ==="
echo " listing volumes :"
../build/bin/dvol -a
echo ""