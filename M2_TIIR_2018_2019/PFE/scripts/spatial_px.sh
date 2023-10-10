#!/usr/bin/env bash

read -p "How many process do you want to spawn ? : " NB_THREADS

SCRIPT=$(pwd)/src/spatial_px.py
OUT_DIR=$(pwd)/out/spatial_px

mkdir -p $OUT_DIR/men $OUT_DIR/med $OUT_DIR/std

img_arr=(./screenshot/*.jpg)

PS3='Please choose an operation : '
options=("mean" "median" "std" "Quit")
select opt in "${options[@]}"
do
    case $opt in
        "mean")
            calculate=1
            c=0
            break
            ;;
        "median")
            calculate=2
            c=1
            break
            ;;
        "std")
            calculate=3
            c=2
            break
            ;;
        "Quit")
            break
            ;;
        *) echo "invalid option $REPLY";;
    esac
done


for ((i=0; i<${#img_arr[@]}; i=i+$NB_THREADS)); do

    for ((j=0; j<$NB_THREADS; j=j+1)); do
        filename=$(basename ${img_arr[$(($j+$i))]} .jpg)
        out="$OUT_DIR/$filename""_""${options[$c]}.jpg"
        echo "Processing $out ......"
        python3 $SCRIPT -i "${img_arr[$i]}" -o  $out -c $calculate &

        mv $OUT_DIR/*_median.jpg $OUT_DIR/med 2> /dev/null
        mv $OUT_DIR/*_mean.jpg $OUT_DIR/men  2> /dev/null
        mv $OUT_DIR/*_std.jpg $OUT_DIR/std  2> /dev/null
    done

    wait

done

exit 0