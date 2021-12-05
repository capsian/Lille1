#!/bin/bash

echo "Creating admin group && creating user admin && adding it to admin group"
sudo addgroup admin
sudo adduser --disabled-password --ingroup admin admin

echo "Creating groupe_a group && creating user lambda_a && adding it to groupe_a group"
sudo addgroup groupe_a
sudo adduser --no-create-home --disabled-password --ingroup groupe_a lambda_a

echo "Creating groupe_b group && creating user lambda_b && adding it to groupe_b group"
sudo addgroup groupe_b
sudo adduser --no-create-home --disabled-password --ingroup groupe_b lambda_b

echo "Creating dir_a dir_b dir_c"
mkdir dir_a dir_b dir_c

echo "Changing dir_a permissions: admin:group_a && ug+rwx,o-rwx,g+s,+t"
sudo chown admin:groupe_a dir_a
sudo chmod ug+rwx,o-rwx,g+s,+t dir_a
echo "Changing dir_a permissions: admin:group_b && ug+rwx,o-rwx,g+s,+t"
sudo chown admin:groupe_b dir_b
sudo chmod ug+rwx,o-rwx,g+s,+t dir_b
echo "Changing dir_c permissions: admin && a+rwx,o-w"
sudo chown admin: dir_c
sudo chmod a+rwx,o-w dir_c

sudo -u lambda_a bash -c 'mkdir dir_a/lambda_a'
sudo -u lambda_a bash -c 'echo "hello from lambda_a: dira_a/lambda_a/lambda_a.txt" > dir_a/lambda_a/lambda_a.txt'
sudo -u lambda_b bash -c 'mkdir dir_b/lambda_b'
sudo -u lambda_b bash -c 'echo "hello from lambda_b: dira_a/lambda_b/lambda_b.txt" > dir_b/lambda_b/lambda_b.txt'
sudo -u admin bash -c 'mkdir dir_c/admin'
sudo -u admin bash -c 'echo "hello from admin: dira_c/admin/admin.txt" > dir_c/admin/admin.txt'


echo "Creating /home/admin/passwd2 and setting permissions"
sudo -u admin bash -c 'touch /home/admin/passwd2'
sudo -u admin bash -c 'chmod o-rwx /home/admin/passwd2'

echo "Compiling ..."
make
echo "Setting permissions: owned by root and set-uid for users"
sudo chown root:root groupe_server groupe_server_udp
sudo chmod +x groupe_server groupe_client groupe_client_udp groupe_client_udp
sudo chown admin:admin pwg
sudo chmod +x,u+s pwg
sudo chmod u+s groupe_server groupe_server_udp

echo "lambda_a tests"
echo " lambda_a trying to set passwd for first time"
sudo -u lambda_a bash -c 'echo -e "lambda_a" | ./pwg'

echo "lambda_b tests"
echo " lambda_b trying to set passwd for first time"
sudo -u lambda_b bash -c 'echo -e "lambda_b" | ./pwg'
