#!/usr/bin/env bash

read -p "How many process do you want to spawn ? : " NB_THREADS

SCRIPT=$(pwd)/src/spatial_square.py
OUT_DIR=$(pwd)/out/spatial_square


img_arr=(./screenshot/*.jpg)

read -p "Enter block edge length (2,3,...,) :  " EDGE
read -p "Enter threshold, 0 otherwise .... : " THRESHOLD

mkdir -p $OUT_DIR $OUT_DIR/$EDGE $OUT_DIR/$EDGE/men $OUT_DIR/$EDGE/med $OUT_DIR/$EDGE/std

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
            exit 0
            ;;
        *) echo "invalid option $REPLY";;
    esac
done


for ((i=0; i<${#img_arr[@]}; i=i+$NB_THREADS)); do

    for ((j=0; j<$NB_THREADS; j=j+1)); do
        filename=$(basename ${img_arr[$(($j+$i))]} .jpg)
        out="$OUT_DIR/$EDGE/$filename""_""${options[$c]}.jpg"
        echo "Processing $out ......"

        if [[ -n "$THRESHOLD" ]]; then
            python3 $SCRIPT -i "${img_arr[$i]}" -o $out -e $EDGE -c $calculate -t $THRESHOLD &
        else
            python3 $SCRIPT -i "${img_arr[$i]}" -o $out -e $EDGE -c $calculate &
        fi

        mv $OUT_DIR/$EDGE/*_median.jpg $OUT_DIR/$EDGE/med 2> /dev/null
        mv $OUT_DIR/$EDGE/*_mean.jpg $OUT_DIR/$EDGE/men  2> /dev/null
        mv $OUT_DIR/$EDGE/*_std.jpg $OUT_DIR/$EDGE/std  2> /dev/null
    done

    wait

done