#!/bin/bash

echo "lambda_a tests"
echo " lambda_a trying to delete dir_b/lambda_b.txt"
sudo -u lambda_a bash -c 'echo -e "lambda_a" | ./rmg dir_b/lambda_b.txt'
echo " lambda_a trying to delete dir_a/lambda_a.txt (wrong password)"
sudo -u lambda_a bash -c 'echo -e "hello" | ./rmg dir_a/lambda_a.txt'
echo " lambda_a trying to delete dir_a/lambda_a.txt (correct password)"
sudo -u lambda_a bash -c 'echo -e "lambda_a" | ./rmg dir_a/lambda_a.txt'

echo "lambda_b tests"
echo " lambda_b trying to delete dir_a/lambda_a.txt"
sudo -u lambda_b bash -c 'echo "lambda_b" | ./rmg dir_a/lambda_a.txt'
echo " lambda_b trying to delete dir_b/lambda_b.txt (wrong password)"
sudo -u lambda_b bash -c 'echo "hello" | ./rmg dir_b/lambda_b.txt'
echo " lambda_b trying to delete dir_a/lambda_a.txt (correct password)"
sudo -u lambda_b bash -c 'echo "lambda_b" | ./rmg dir_b/lambda_b.txt'