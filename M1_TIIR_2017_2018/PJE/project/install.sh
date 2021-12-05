#!/usr/bin/env bash

echo "BUILDING PROJECT .... "
cd ./smews && scons target=mbed_ethernet apps=:project ipaddr=192.168.1.2
echo " DONE !"

echo -n "INSTALLING THE PROJECT"
cp ./bin/mbed_ethernet/smews.bin /media/$USER/MBED
echo " DONE ! "
echo "OPEN http://192.168.1.2 !"