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
sudo chown admin dir_c
sudo chmod a+rwx,o-w dir_c

echo "Creating /home/admin/passwd and setting permissions"
sudo -u admin bash -c 'touch /home/admin/passwd2'
sudo -u admin bash -c 'chmod o-rwx /home/admin/passwd2'

echo "Compiling pwg"
make
echo "Setting pwg permissions: owned by admin and set-uid for users"
sudo chown admin pwg
sudo chmod +x,u+s pwg

echo "Creating file for lambda_a"
sudo -u lambda_a bash -c 'echo "hello from lambda_a" > dir_a/lambda_a.txt'
echo "Creating file for lambda_b"
sudo -u lambda_b bash -c 'echo "hello from lambda_b" > dir_b/lambda_b.txt'