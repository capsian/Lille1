#!/usr/bin/env bash

echo "" > ./test/output/resSizeDebit_single.txt

tmp_ret=0
svIP=192.168.10.2

for i in `seq 1 25 2000`
do
    echo "SINGLE $i"
    echo "SINGLE $i" >> ./test/output/resSizeDebit_single.txt
    val_moy_s=0

    for k in `seq 0 1 9`
    do
      echo "for loop " $k
      val[$k]=$(./build/bin/client $svIP 2048 $i 1)
      tmp_ret=$(echo $?)
      while [ $tmp_ret -ne 0 ]
      do
        sleep 1
        val[$k]=$(./build/bin/client $svIP 2048 $i 1)
        tmp_ret=$(echo $?)
      done
      #echo " tmp_ret =  $tmp_ret , val[$k] = " ${val[$k]}
      val_moy_s=$(($val_moy_s + ${val[$k]}))
      echo " ${val[$k]} $i" >> ./test/output/resSizeDebit_single.txt
    done

    val_moy_s=$(($val_moy_s / 10))

    echo "  $val_moy_s $i" >> ./test/output/resSizeDebit_single.txt
done

for i in `seq 2001 500 50000`
#for i in `seq 6001 500 50000`
do
    echo "SINGLE $i"
    echo "SINGLE $i" >> ./test/output/resSizeDebit_single.txt

    val_moy_s=0

    for k in `seq 0 1 9`
    do
      echo "for loop " $k
      val[$k]=$(./build/bin/client $svIP 2048 $i 1)
      tmp_ret=$(echo $?)
      while [ $tmp_ret -ne 0 ]
      do
        sleep 1
        val[$k]=$(./build/bin/client $svIP 2048 $i 1)
        tmp_ret=$(echo $?)
      done
      #echo " tmp_ret =  $tmp_ret , val[$k] = " ${val[$k]}
      val_moy_s=$(($val_moy_s + ${val[$k]}))
      echo " ${val[$k]} $i" >> ./test/output/resSizeDebit_single.txt
    done

    val_moy_s=$(($val_moy_s / 10))
    echo "  $val_moy_s $i" >> ./test/output/resSizeDebit_single.txt
done

for i in `seq 50000 500 60000`
do

    echo "SINGLE $i"
    echo "SINGLE $i" >> ./test/output/resSizeDebit_single.txt
    val_moy_s=0

    for k in `seq 0 1 9`
    do
      echo "for loop " $k
      val[$k]=$(./build/bin/client $svIP 2048 $i 1)
      tmp_ret=$(echo $?)
      while [ $tmp_ret -ne 0 ]
      do
        sleep 1
        val[$k]=$(./build/bin/client $svIP 2048 $i 1)
        tmp_ret=$(echo $?)
      done
      #echo " tmp_ret =  $tmp_ret , val[$k] = " ${val[$k]}
      val_moy_s=$(($val_moy_s + ${val[$k]}))
      echo " ${val[$k]} $i" >> ./test/output/resSizeDebit_single.txt
    done

    val_moy_s=$(($val_moy_s / 10))
    echo "  $val_moy_s $i" >> ./test/output/resSizeDebit_single.txt
done

#cat ./test/conf/size_debit_s.conf | gnuplot

exit 0
