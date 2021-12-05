#!/usr/bin/env bash

echo ""
echo "== LILLE =="
../build/main ./input/input_lille.ini > ./output/main_lille.out
python3 ./gantt.py ./input/input_lille.ini ./output/main_lille.out > ./output/out_lille.svg

echo ""
echo "== GRENOBLE =="
../build/main ./input/input_grenoble.ini > ./output/main_grenoble.out
python3 ./gantt.py ./input/input_grenoble.ini ./output/main_grenoble.out > ./output/out_grenoble.svg

echo ""
echo "== NANCY =="
../build/main ./input/input_nancy.ini > ./output/main_nancy.out
python3 ./gantt.py ./input/input_nancy.ini ./output/main_nancy.out > ./output/out_nancy.svg

echo ""
echo "== LYON =="
../build/main ./input/input_lyon.ini > ./output/main_lyon.out
python3 ./gantt.py ./input/input_lyon.ini ./output/main_lyon.out > ./output/out_lyon.svg
