#!/usr/bin/env bash

echo "" > ./test/output/resSizeDebit_multi.txt

tmp_ret=0
svIP=192.168.10.1

echo "========== size = 1500 ==========" >> ./test/output/resSizeDebit_multi.txt
size_multi=1500

# MULTI
for tmp_thrd in `seq 1 1 20`
do

    echo "MULTI $tmp_thrd"
    echo "MULTI $tmp_thrd" >> ./test/output/resSizeDebit_multi.txt
    val_moy_s=0

	for k in `seq 0 1 9`
  do
      echo "for loop " $k
      val[$k]=$(./build/bin/client $svIP 2048 $size_multi $tmp_thrd)
      tmp_ret=$(echo $?)
      while [ $tmp_ret -ne 0 ]
      do
        sleep 1
        val[$k]=$(./build/bin/client $svIP 2048 $size_multi $tmp_thrd)
        tmp_ret=$(echo $?)
      done
      #echo " tmp_ret =  $tmp_ret , val[$k] = " ${val[$k]}
      val_moy_s=$(($val_moy_s + ${val[$k]}))
      echo " ${val[$k]} $tmp_thrd" >> ./test/output/resSizeDebit_multi.txt

  done

    val_moy_s=$(($val_moy_s / 10))
    echo "  $val_moy_s $tmp_thrd" >> ./test/output/resSizeDebit_multi.txt

done



echo "========== size = 2000 ==========" >> ./test/output/resSizeDebit_multi.txt
size_multi=2000

# MULTI
for tmp_thrd in `seq 1 1 20`
do

    echo "MULTI $tmp_thrd"
    echo "MULTI $tmp_thrd" >> ./test/output/resSizeDebit_multi.txt
    val_moy_s=0

	for k in `seq 0 1 9`
  do
      echo "for loop " $k
      val[$k]=$(./build/bin/client $svIP 2048 $size_multi $tmp_thrd)
      tmp_ret=$(echo $?)
      while [ $tmp_ret -ne 0 ]
      do
        sleep 1
        val[$k]=$(./build/bin/client $svIP 2048 $size_multi $tmp_thrd)
        tmp_ret=$(echo $?)
      done
      #echo " tmp_ret =  $tmp_ret , val[$k] = " ${val[$k]}
      val_moy_s=$(($val_moy_s + ${val[$k]}))
      echo " ${val[$k]} $tmp_thrd" >> ./test/output/resSizeDebit_multi.txt

  done

    val_moy_s=$(($val_moy_s / 10))
    echo "  $val_moy_s $tmp_thrd" >> ./test/output/resSizeDebit_multi.txt

done

echo "========== size = 50000 ==========" >> ./test/output/resSizeDebit_multi.txt
size_multi=50000

# MULTI
for tmp_thrd in `seq 1 1 20`
do

    echo "MULTI $tmp_thrd"
    echo "MULTI $tmp_thrd" >> ./test/output/resSizeDebit_multi.txt
    val_moy_s=0

	for k in `seq 0 1 9`
  do
      echo "for loop " $k
      val[$k]=$(./build/bin/client $svIP 2048 $size_multi $tmp_thrd)
      tmp_ret=$(echo $?)
      while [ $tmp_ret -ne 0 ]
      do
        sleep 1
        val[$k]=$(./build/bin/client $svIP 2048 $size_multi $tmp_thrd)
        tmp_ret=$(echo $?)
      done
      #echo " tmp_ret =  $tmp_ret , val[$k] = " ${val[$k]}
      val_moy_s=$(($val_moy_s + ${val[$k]}))
      echo " ${val[$k]} $tmp_thrd" >> ./test/output/resSizeDebit_multi.txt

  done

    val_moy_s=$(($val_moy_s / 10))
    echo "  $val_moy_s $tmp_thrd" >> ./test/output/resSizeDebit_multi.txt

done

#cat ./test/conf/size_debit_m.conf | gnuplot
