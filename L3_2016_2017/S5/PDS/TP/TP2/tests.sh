#!/bin/bash

echo "  du -b test_dir"
du -b test_dir
echo "  ./mdu -b test_dir"
./mdu -b test_dir
echo "  du -B 512 test_dir"
du  -B 512 test_dir
echo "  ./mdu test_dir"
./mdu test_dir

echo ""
echo "Résultat incorrect avec option L"
echo ""


echo "  du -Lb test_dir"
du -Lb test_dir
echo "  ./mdu -Lb test_dir"
./mdu -Lb test_dir/1
./mdu -Lb test_dir/2
./mdu -Lb test_dir/3
./mdu -Lb test_dir
echo "  du -LB 512 test_dir"
du  -LB 512 test_dir
echo "  ./mdu -L test_dir"
./mdu -L test_dir/1
./mdu -L test_dir/2
./mdu -L test_dir/3
./mdu -L test_dir






