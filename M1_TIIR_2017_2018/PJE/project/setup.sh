#!/usr/bin/env bash

echo -n "SETUP ETHERNET .... "
sudo ifconfig enp3s0 up
sudo ifconfig enp3s0 192.168.1.3
echo " DONE !"
