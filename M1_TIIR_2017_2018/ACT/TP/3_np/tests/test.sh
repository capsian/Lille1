#!/usr/bin/env bash

echo ""
echo "=== test verif ==="
../build/main ./donneesTest/tasks_input.ini verif 0 < ./donneesTest/input_certif_ok.ini
echo ""

../build/main ./donneesTest/tasks_input.ini verif 0 < ./donneesTest/input_certif_ko.ini
echo ""

echo "=== test nondet ==="
../build/main ./donneesTest/tasks_input.ini nondet 0
../build/graphToVisu out.grp out1.ps
echo ""


#echo "=== test PART ==="
#../build/main ./donneesTest/exPart1 part 1
#../build/graphToVisu out.grp out2.ps
#echo ""


echo "=== test exhaust 1 ==="
../build/main ./donneesTest/tasks_input.ini exhaust 1
../build/graphToVisu out.grp out3.ps
echo ""

echo "=== test exhaust 2 ==="
../build/main ./donneesTest/tasks_input_big.ini exhaust 1
../build/graphToVisu out.grp out4.ps
echo ""

echo "=== test exhaust 3 ==="
../build/main ./donneesTest/donnee1_1 exhaust 1
../build/graphToVisu out.grp out5.ps
echo ""

echo "=== test exhaust 4 ==="
../build/main ./donneesTest/donnee1_2 exhaust 1
../build/graphToVisu out.grp out6.ps
echo ""

echo "=== test exhaust 5 ==="
../build/main ./donneesTest/donnee4_1 exhaust 1
../build/graphToVisu out.grp out7.ps
echo ""

echo "=== test exhaust 6 ==="
../build/main ./donneesTest/donnee4_2 exhaust 1
../build/graphToVisu out.grp out8.ps
echo ""
