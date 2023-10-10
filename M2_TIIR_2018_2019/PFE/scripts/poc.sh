#!/usr/bin/env bash

NB_THREADS=3
CMD='python3 '                          # CMD
OD='out_poc1'                           # OUTPUT_DIR
GSS='src/tor_square.py'           # grayscale_square script
STS='src/temporal_square.py'      # spatiotemporal_square script
IMG1='screenshot/IMG_00001.jpg'
IMG2='screenshot/IMG_00002.jpg'
IMG3='screenshot/IMG_00003.jpg'

echo "POC"

mkdir -p $OD

echo "Calculate std and apply threshold ... "
read -p "Enter threshold min val : " MIT
read -p "Enter threshold max val : " MAT

# format cmd
CMD1=$CMD$STS
echo $CMD1
OI1=()                          # out image 1
for (( t=$MIT; t<=$MAT; t+=$NB_THREADS ))
do
    for ((j=0; j<$NB_THREADS; j=j+1)); do
        $CMD1 -o $IMG2 -p $IMG1 -f $IMG3 -e 2 -t $t -c 3 -out $OD/img_1_3_std_t$(($t+$j)).jpg &
        OI1+=( $OD/img_1_3_std_t$(($t+$j)).jpg )
    done
    wait
done

echo "apply grayscale ... "
read -p "Enter max edge val : " ME

# format cmd
CMD2=$CMD$GSS
for elem in ${OI1[@]}
do
    II=$elem
    for (( e=2; e<=$ME; e++ ))
    do
        OI="${II[@]:0:${#II[@]}-5}_tor1e$e.jpg"
        echo "$II => $OI"
        $CMD2 -i $II -e $e -t 1 -o $OI
        II=$OI
    done
done
