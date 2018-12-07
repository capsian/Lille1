#!/usr/bin/env bash

echo ""
echo ""
echo "================="
echo "Testing drive.o ..."
echo "================="
echo ""
echo ""


echo "=== dmps === "

echo "dmps 0 0 ==== affiche à partir du 12eme octets (n'affiche pas le MBR)"
../build/bin/dmps 0 0

echo "dmps 1 1"

../build/bin/dmps 1 1

echo "dmps 0 15"

../build/bin/dmps 0 15

echo "dmps 15 0"

../build/bin/dmps 15 0

echo "dmps 15 15"

../build/bin/dmps 15 15

echo "dmps 16 16"

../build/bin/dmps 16 16


echo "=== frmt === "
echo -n "frmt 0 0"

../build/bin/frmt 0 0
echo " ... DONE ! "

echo "dmps 0 0"

../build/bin/dmps 0 0

echo -n "frmt 1 1"

../build/bin/frmt 1 1
echo " ... DONE ! "

echo "dmps 1 1"

../build/bin/dmps 1 1

echo "time frmt -a"

time ../build/bin/frmt -a

echo "time frmt -r"

time ../build/bin/frmt -r

echo "=== od === "

echo "MBR (12 octets)"

od -x --endian=big -N12 vdiskA.bin

echo "cyl 0 sec 0 (display bloc 256 octets)"

od -x --endian=big -j13 -N256 vdiskA.bin

echo "cyl 0 sec 1 (jmp: 12 + 256)"

od -x --endian=big -j268 -N256 vdiskA.bin

echo "cyl 0 sec 2 (jmp: 268 + 256)"

od -x --endian=big -j524 -N256 vdiskA.bin