#!/bin/bash

echo "User lambda_b"
echo

echo "  dir_a tests"
echo "    ls -al dir_a"
sudo -u lambda_b bash -c 'ls -al dir_a'
echo "    mkdir dir_a/lambda_b"
sudo -u lambda_b bash -c 'mkdir dir_a/lambda_b'
echo "    cat dir_a/admin.txt"
sudo -u lambda_b bash -c 'cat dir_a/admin.txt'
echo '    echo "hello from lambda_b: dira_a/lambda_b/lambda_b.txt" > dir_a/lambda_b/lambda_b.txt'
sudo -u lambda_b bash -c 'echo "hello from lambda_b: dira_a/lambda_b/lambda_b.txt" > dir_a/lambda_b/lambda_b.txt'
echo "    mv dir_a/admin.txt dira_a/admin_lambda_b.txt"
sudo -u lambda_b bash -c 'mv dir_a/admin.txt dira_a/admin_lambda_b.txt'
echo "    rm dir_a/admin.txt"
sudo -u lambda_b bash -c 'rm dir_a/admin.txt'


echo "  dir_c tests"
echo "    ls -al dir_c"
sudo -u lambda_b bash -c 'ls -al dir_c'
echo "    mkdir dir_c/lambda_b"
sudo -u lambda_b bash -c 'mkdir dir_c/lambda_b'
echo "    cat dir_c/admin.txt"
sudo -u lambda_b bash -c 'cat dir_c/admin.txt'
echo '    echo "hello from lambda_b: dira_c/lambda_b.txt" > dira_c/lambda_b.txt'
sudo -u lambda_b bash -c 'echo "hello from lambda_b: dira_c/lambda_b.txt" > dira_c/lambda_b.txt'
echo "    mv dira_c/admin.txt dira_c/admin_lambda_b.txt"
sudo -u lambda_b bash -c 'mv dir_c/admin.txt dir_c/admin_lambda_b.txt'
echo "    rm dira_c/admin.txt"
sudo -u lambda_b bash -c 'rm dir_c/admin.txt'

echo "  dir_b tests"
echo "    ls -al dir_b"
sudo -u lambda_b bash -c 'ls -al dir_b'
echo "    mkdir dir_b/lambda_b"
sudo -u lambda_b bash -c 'mkdir dir_b/lambda_b'
echo "    cat dir_b/admin.txt"
sudo -u lambda_b bash -c 'cat dir_b/admin.txt'
echo '    echo "hello from lambda_b: dir_b/lambda_b.txt" > dir_b/lambda_b.txt'
sudo -u lambda_b bash -c 'echo "hello from lambda_b: dir_b/lambda_b.txt" > dir_b/lambda_b.txt'
echo "    mv dir_b/admin.txt dir_b/admin_lambda_b.txt"
sudo -u lambda_b bash -c 'mv dir_b/admin.txt dir_b/admin_lambda_b.txt'
echo "    rm dir_b/admin.txt"
sudo -u lambda_b bash -c 'rm dir_b/admin.txt'
