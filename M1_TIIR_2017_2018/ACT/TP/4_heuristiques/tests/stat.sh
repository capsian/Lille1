#!/usr/bin/env bash

mkdir -p output

echo ""
echo "== STAT LILLE =="
../build/main input/input_lille.ini 1 > output/stat_lille.out
echo " DONE ! "

echo ""
echo "== STAT GRENOBLE =="
../build/main input/input_grenoble.ini 1 > output/stat_grenoble.out
echo " DONE ! "

echo ""
echo "== STAT LYON =="
../build/main input/input_lyon.ini 1 > output/stat_lyon.out
echo " DONE ! "

echo ""
echo "== STAT NANCY =="
../build/main input/input_nancy.ini 1 > output/stat_nancy.out
echo " DONE ! "