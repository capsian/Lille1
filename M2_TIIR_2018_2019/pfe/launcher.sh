#!/usr/bin/env bash

clear
echo "Holla !! this script is toooooo ollllddd ... fix paths !!!!"
echo "bye ...."

exit 0

echo -n "Cheking for screenshot folder ...."
if [ ! -d "screenshot" ]; then
    echo "Not found ! getting it from screenshots branch .... "
    mkdir screenshot
    git checkout screenshots v1_0_50.tar.xz
    tar -xvf v1_0_50.tar.xz -C screenshot
    rm -rf v1_0_50.tar.xz
    echo "Done !!"
else
    echo "Done !"
fi

PS3='Please enter your choice: '
options=("spatial_px" "spatial_square" "spatiotemporal_px" "spatiotemporal_square" "spatiotemporal_px2" "tests" "poc" "Quit")
select opt in "${options[@]}"
do
    case $opt in
        "spatial_px")
            ./scripts/spatial_px.sh
            ;;
        "spatial_square")
            ./scripts/spatial_square.sh
            ;;
        "spatiotemporal_px")
            ./scripts/spatiotemporal_px.sh
            ;;
        "spatiotemporal_px2")
            ./scripts/spatiotemporal_px2.sh
            ;;
        "spatiotemporal_square")
            ./scripts/spatiotemporal_square.sh
            ;;
        "tests")
            ./scripts/tests.sh
            ;;
        "poc")
            ./scripts/poc.sh
            ;;
        "Quit")
            break
            ;;
        *) echo "invalid option $REPLY";;
    esac
done


echo "Cleaning ...."
rm -rf screenshot

echo "Adios ..."

exit 0
