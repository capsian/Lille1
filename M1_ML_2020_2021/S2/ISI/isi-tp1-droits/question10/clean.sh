#!/bin/bash

sudo rm -rf dir_*
sudo deluser lambda_a && sudo deluser lambda_b && sudo deluser admin
sudo delgroup groupe_a && sudo delgroup groupe_b && sudo delgroup admin
sudo rm /home/admin/passwd2
