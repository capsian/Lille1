#!/bin/bash

echo "User lambda_a"
echo

echo "  dir_a tests"
echo "    ls -al dir_a"
sudo -u lambda_a bash -c 'ls -al dir_a'
echo "    mkdir dir_a/lambda_a"
sudo -u lambda_a bash -c 'mkdir dir_a/lambda_a'
echo "    cat dir_a/admin.txt"
sudo -u lambda_a bash -c 'cat dir_a/admin.txt'
echo '    echo "hello from lambda_a: dira_a/lambda_a/lambda_a.txt" > dir_a/lambda_a/lambda_a.txt'
sudo -u lambda_a bash -c 'echo "hello from lambda_a: dira_a/lambda_a/lambda_a.txt" > dir_a/lambda_a/lambda_a.txt'
echo "    mv dir_a/admin.txt dira_a/admin_lambda_a.txt"
sudo -u lambda_a bash -c 'mv dir_a/admin.txt dira_a/admin_lambda_a.txt'
echo "    rm dir_a/admin.txt"
sudo -u lambda_a bash -c 'rm dir_a/admin.txt'


echo "  dir_c tests"
echo "    ls -al dir_c"
sudo -u lambda_a bash -c 'ls -al dir_c'
echo "    mkdir dir_c/lambda_a"
sudo -u lambda_a bash -c 'mkdir dir_c/lambda_a'
echo "    cat dir_c/admin.txt"
sudo -u lambda_a bash -c 'cat dir_c/admin.txt'
echo '    echo "hello from lambda_a: dira_c/lambda_a.txt" > dira_c/lambda_a.txt'
sudo -u lambda_a bash -c 'echo "hello from lambda_a: dira_c/lambda_a.txt" > dira_c/lambda_a.txt'
echo "    mv dira_c/admin.txt dira_c/admin_lambda_a.txt"
sudo -u lambda_a bash -c 'mv dir_c/admin.txt dir_c/admin_lambda_a.txt'
echo "    rm dira_c/admin.txt"
sudo -u lambda_a bash -c 'rm dir_c/admin.txt'

echo "  dir_b tests"
echo "    ls -al dir_b"
sudo -u lambda_a bash -c 'ls -al dir_b'
echo "    mkdir dir_b/lambda_a"
sudo -u lambda_a bash -c 'mkdir dir_b/lambda_a'
echo "    cat dir_b/admin.txt"
sudo -u lambda_a bash -c 'cat dir_b/admin.txt'
echo '    echo "hello from lambda_a: dir_b/lambda_a.txt" > dir_b/lambda_a.txt'
sudo -u lambda_a bash -c 'echo "hello from lambda_a: dir_b/lambda_a.txt" > dir_b/lambda_a.txt'
echo "    mv dir_b/admin.txt dir_b/admin_lambda_a.txt"
sudo -u lambda_a bash -c 'mv dir_b/admin.txt dir_b/admin_lambda_a.txt'
echo "    rm dir_b/admin.txt"
sudo -u lambda_a bash -c 'rm dir_b/admin.txt'
