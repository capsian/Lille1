#!/usr/bin/env bash

SCRIPT=$(pwd)/src/spatiotemporal_square.py
OUT_DIR=$(pwd)/out/spatiotemporal_square

mkdir -p $OUT_DIR

img_arr=(./screenshot/*.jpg)

read -p "Enter origin (central) image number, we will take img=[0,..,CENTRAL,...,2*CENTRAL], [0..49] : " ORIGIN

past_img_arr=("${img_arr[@]:0:$(($ORIGIN))}")
past_img_arr=$(printf " %s " "${past_img_arr[@]}")
future_img_arr=("${img_arr[@]:$(($ORIGIN+1)):$(($ORIGIN))}")
future_img_arr=$(printf " %s " "${future_img_arr[@]}")
org_img=${img_arr[$ORIGIN]}

echo " past_img_arr   : $past_img_arr"
echo " org_img        : $org_img"
echo " future_img_arr : $future_img_arr"

read -p "Enter result file (file.jpg) : " FILENAME

read -p "Enter block edge length (2,3,...,) :  " EDGE
read -p "Enter threshold, 0 otherwise .... : " THRESHOLD
read -p "Enter skip, 0 otherwise .... : " SKIP

mkdir -p $OUT_DIR/$EDGE
FILENAME=$OUT_DIR/$EDGE/$FILENAME

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

if [[ -n "$THRESHOLD" ]]; then
    if [[ -n "$SKIP" ]]; then
        python3 $SCRIPT -o $org_img -p $past_img_arr -f $future_img_arr -e $EDGE -out $FILENAME -c $calculate -t $THRESHOLD -s $SKIP &
    else
        python3 $SCRIPT -o $org_img -p $past_img_arr -f $future_img_arr -e $EDGE -out $FILENAME -c $calculate -t $THRESHOLD &
    fi
else
    if [[ -n "$SKIP" ]]; then
        python3 $SCRIPT -o $org_img -p $past_img_arr -f $future_img_arr -e $EDGE -out $FILENAME -c $calculate -s $SKIP &
    else
        python3 $SCRIPT -o $org_img -p $past_img_arr -f $future_img_arr -e $EDGE -out $FILENAME -c $calculate &
    fi
fi

exit 0