#!/usr/bin/env bash

read m n i j

I=$(($m-$i-1))
J=$(($n-$j-1))

echo "f($m,$n,$i,$j) : "
echo "$m $n $i $j" | ./dyn_sym_minimal_space

echo "f($m,$n,$I,$j) : "
echo "$m $n $I $j" | ./dyn_sym_minimal_space

echo "f($m,$n,$i,$J) : "
echo "$m $n $i $J" | ./dyn_sym_minimal_space

echo "f($m,$n,$I,$J) : "
echo "$m $n $I $J" | ./dyn_sym_minimal_space

echo "============"

echo "f($n,$m,$j,$i) : "
echo "$n $m $j $i" | ./dyn_sym_minimal_space

echo "f($n,$m,$j,$I) : "
echo "$n $m $j $I" | ./dyn_sym_minimal_space

echo "f($n,$m,$J,$i) : "
echo "$n $m $J $i" | ./dyn_sym_minimal_space

echo "f($n,$m,$J,$I) : "
echo "$n $m $J $I" | ./dyn_sym_minimal_space