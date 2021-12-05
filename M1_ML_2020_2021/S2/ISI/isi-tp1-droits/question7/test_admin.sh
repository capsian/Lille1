#!/bin/bash

echo "dir_a tests ..."
echo "Creating file dir_a/admin.txt"
sudo -u admin bash -c 'echo "Hello from admin: dir_a/admin.txt" > dir_a/admin.txt'
echo "Viewing file dir_a/admin.txt"
sudo -u admin bash -c 'cat dir_a/admin.txt'
echo "Removing file dir_a/admin.txt"
sudo -u admin bash -c 'rm dir_a/admin.txt'

echo "dir_b tests ..."
echo "Creating file dir_b/admin.txt"
sudo -u admin bash -c 'echo "Hello from admin: dir_b/admin.txt" > dir_b/admin.txt'
echo "Viewing file dir_b/admin.txt"
sudo -u admin bash -c 'cat dir_b/admin.txt'
echo "Removing file dir_b/admin.txt"
sudo -u admin bash -c 'rm dir_b/admin.txt'

echo "dir_c tests ..."
echo "Creating file dir_c/admin.txt"
sudo -u admin bash -c 'echo "Hello from admin: dir_c/admin.txt" > dir_c/admin.txt'
echo "Viewing file dir_c/admin.txt"
sudo -u admin bash -c 'cat dir_c/admin.txt'
echo "Removing file dir_c/admin.txt"
sudo -u admin bash -c 'rm dir_c/admin.txt'

echo "no files should remains ...."
sudo -u admin bash -c 'tree .'

echo "recreating files ....."
sudo -u admin bash -c 'echo "Hello from admin: dir_a/admin.txt" > dir_a/admin.txt'
sudo -u admin bash -c 'echo "Hello from admin: dir_b/admin.txt" > dir_b/admin.txt'
sudo -u admin bash -c 'echo "Hello from admin: dir_c/admin.txt" > dir_c/admin.txt'


echo "Done !"
echo "Go check lambda_a & lambda_b tests !"