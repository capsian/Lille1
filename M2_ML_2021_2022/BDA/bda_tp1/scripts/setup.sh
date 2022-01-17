#!/bin/bash

SSH_PUB_KEY="ssh-rsa AAAAB3NzaC1yc2EAAAADAQABAAABAQCUlnZvEVJO/XPAOXjdiWkByDPR67LPRZ1wByXUQeNPPym3td+Rk23lbcpv0VvSnNm91SF2TlXVok4sTmqChZmJF5rOxHAUb57YnlsWl3hN1Q7Tm8aGDoFt/En5AA+vYFBPFKJtcSglA8mBIBajLQKlIXW2eU8RQ7g/hwFzkgv56i1dqejKOnG1AS0l5yRIGqjZhlbNMQBdThLU7pulPWw68bJHmW1iAbJcaHHn2i981WMRLdc8xN2MWmvVRpJmmD0SE1ZBHy7jMelU99/VctbGXETviyLyj0sMZu7sMoZIdxn28PNHCJ7VR9R9m3O4Sm/mBhbX8P5q5yad5Pfi3cIp cha@serveur"

echo "Post Process: add lakhdar ssh key for git !!!"
echo "Done !"
echo 

# Updating root password
echo "Updating root password (cloud) to root:root1234"
su root -c "passwd"
echo "Done !"
echo

echo "Updating ubuntu password to ubuntu (with user root)"
su root -c "passwd ubuntu"
echo "Done !"
echo 

# Adding user
echo "Adding user cha1:cha1 ... (with user ubuntu)"
sudo adduser cha1
echo "Done !"
echo

# Init ssh for cha1
echo "Init ssh for cha1 (with user cha1)"
su cha1 -c "ssh-keygen"
echo "Done !"
echo

# Associate ssh
echo "Associating ssh key for cha1 (with root)"
su root -c "echo \"$SSH_PUB_KEY\" > /home/cha1/.ssh/known_hosts"
echo "Done !"
echo

# Install postgresql
echo "Install postgres"
sudo sh -c 'echo "deb http://apt.postgresql.org/pub/repos/apt $(lsb_release -cs)-pgdg main" > /etc/apt/sources.list.d/pgdg.list'
wget --quiet -O - https://www.postgresql.org/media/keys/ACCC4CF8.asc | sudo apt-key add -
sudo apt-get update
sudo apt-get -y install postgresql

echo "Done !"
echo

# Add firewall
echo "Enable ufw"
sudo ufw enable
echo
echo "Add firewall rules"
sudo ufw allow from 172.28.100.140 to any port 5432
sudo ufw allow from 172.28.100.203 to any port 5432
echo "Done !"
echo
echo "Check "
sudo ufw status
echo

exit 0
