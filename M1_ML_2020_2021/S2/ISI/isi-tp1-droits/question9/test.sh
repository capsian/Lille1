#!/bin/bash

echo "lambda_a tests"
echo " lambda_a trying to set passwd for first time"
sudo -u lambda_a bash -c 'echo -e "lambda_a" | ./pwg'
echo " lambda_a trying to change passwd with wrong old one"
sudo -u lambda_a bash -c 'echo -e "lambda_b\nHello" | ./pwg'
echo " lambda_a trying to change passwd with right old one"
sudo -u lambda_a bash -c 'echo -e "lambda_a\nlambda_a" | ./pwg'

echo "lambda_b tests"
echo " lambda_b trying to set passwd for first time"
sudo -u lambda_b bash -c 'echo -e "lambda_b" | ./pwg'
echo " lambda_b trying to change passwd with wrong old one"
sudo -u lambda_b bash -c 'echo -e "lambda_a\nHello" | ./pwg'
echo " lambda_b trying to change passwd with right old one"
sudo -u lambda_b bash -c 'echo -e "lambda_b\nlambda_b" | ./pwg'