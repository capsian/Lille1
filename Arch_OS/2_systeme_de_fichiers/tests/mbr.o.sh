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
echo " create new vol; sec=1, cyl=0, block=10"
../build/bin/mkvol -s 1 -c 0 -b 10
echo ""

echo "=== listing volumes ==="
echo " listing volumes :"
../build/bin/dvol -a
echo ""

echo "=== create new volume ==="
echo " create new vol; sec=11, cyl=0, block=15"
../build/bin/mkvol -s 12 -c 0 -b 15
echo ""

echo "=== listing volumes ==="
echo " listing volumes :"
../build/bin/dvol -a
echo ""

echo "=== create new volume ==="
echo " create new vol; sec=10, cyl=10, block=20"
../build/bin/mkvol -s 12 -c 10 -b 20
echo ""

echo "=== listing volumes ==="
echo " listing volumes :"
../build/bin/dvol -a
echo ""