#!/usr/bin/env bash

echo "Testing neighbours !!"
python3 test/get_neighbours_test.py
sleep 2

echo
echo "==========================="
echo

echo "Testing sub matrices !!"
python3 test/sub_matrices_test.py

exit 0