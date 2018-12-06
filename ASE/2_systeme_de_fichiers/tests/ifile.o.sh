#!/usr/bin/env bash

echo ""
echo "================="
echo "Testing ifile.o ..."
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
echo " create new vol; sec=1, cyl=0, blocs=95"
../build/bin/mkvol -s 1 -c 0 -b 95
echo ""
echo " create new vol; sec=1, cyl=6, blocs=16"
../build/bin/mkvol -s 1 -c 6 -b 16
echo ""
echo " create new vol; sec=2, cyl=7, blocs=141"
../build/bin/mkvol -s 2 -c 7 -b 141
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
echo " listing volumes :"
../build/bin/dvol -a
echo ""

echo "=== displaying file system ==="
echo "dfs -a"
../build/bin/dfs -a
echo ""

echo "=== nfile ==="
echo "python -c \"print'c' * (256*70)\" | if_nfile 0"
time python -c "print'c' * (256*70)" | ../build/bin/if_nfile 0
echo ""
echo "python -c \"print'x' * (256*11)\" | if_nfile 1"
time python -c "print'x' * (256*11)" | ../build/bin/if_nfile 1
echo ""

echo "=== pfile ==="
echo "if_pfile 0 1"
../build/bin/if_pfile 0 1
echo ""
echo "if_pfile 1 1"
../build/bin/if_pfile 1 1
echo ""

echo "=== displaying file system ==="
echo "dfs -a"
../build/bin/dfs -a
echo ""

echo "=== delete file ==="
echo "if_dfile 0 1"
../build/bin/if_dfile 0 1
echo ""

echo "=== displaying file system ==="
echo "dfs -a"
../build/bin/dfs -a
echo ""