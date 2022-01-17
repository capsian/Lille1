#!/bin/bash


# Create user ubuntu && creat db
echo "Creating user ubuntu for postgres (with user postgres)"
sudo -u postgres createuser --interactive
echo "Done !"
echo
#echo "Creating database ubuntu for user ubuntu (with user postgres)"
#sudo -u postgres createdb ubuntu
#echo "Done !"
#echo
echo "Update password of user ubuntu in postgreSQL  (with user postgres)"
sudo -u postgres psql -c "ALTER USER ubuntu PASSWORD 'ubuntu';"
echo "Done !"
echo

# Create user cha1 && creat db
echo "Creating user cha1 for postgres (with user postgres)"
sudo -u postgres createuser --interactive
echo "Done !"
echo
#echo "Creating database cha1 for user cha1 (with user postgres)"
#sudo -u postgres createdb cha1
#echo "Done !"
#echo
echo "Update password of user cha1 in postgreSQL  (with user postgres)"
sudo -u postgres psql -c "ALTER USER cha1 PASSWORD 'ILovePostgreSQL';"
echo "Done !"
echo

echo "Update password of user postgres in postgreSQL  (with user postgres)"
sudo -u postgres psql -c "ALTER USER postgres PASSWORD 'postgres';"
echo "Done !"
echo

# enable auth
STR_FIND="#listen_addresses = 'localhost'		# what IP address(es) to listen on;"
STR_RPLC="listen_addresses = '*'				# what IP address(es) to listen on;"
echo "Enabling remote access to postgres"
sudo sed -i "s/$STR_FIND/$STR_RPLC/g" /etc/postgresql/13/main/postgresql.conf
echo "Done !"
echo
echo "Check config file"
cat /etc/postgresql/13/main/postgresql.conf | grep listen
echo
echo "Check open ports"
ss -nlt | grep 5432
echo "Done !"
echo

# Add connec
echo "Enable remote connection for users ubuntu and cha1 (with user root)"
su root -c 'echo "" >> /etc/postgresql/13/main/pg_hba.conf'
su root -c 'echo "# Add users auth" >> /etc/postgresql/13/main/pg_hba.conf'
su root -c 'echo "host    all             ubuntu		0.0.0.0/0		md5" >>   /etc/postgresql/13/main/pg_hba.conf'
su root -c 'echo "host    all             cha1		0.0.0.0/0		md5" >>   /etc/postgresql/13/main/pg_hba.conf'
echo "Done !"
echo "Check ...."
sudo cat /etc/postgresql/13/main/pg_hba.conf
echo

echo "Restart postgres"
sudo service postgresql restart
echo "Done !"
echo

# microblog
echo "Creating database microblog (with user postgres)"
sudo -u postgres createdb microblog
echo "Done !"
echo
echo "Import DB"
cat ./microblog.sql | psql --dbname microblog
echo "Done !"
echo

echo "Change pg_hba.conf to allow common_user without password (with user root)"
su root -c 'echo "host    all             common_user		0.0.0.0/0		trust" >>   /etc/postgresql/13/main/pg_hba.conf'
echo "Done !"
echo

echo "Restart postgres"
sudo service postgresql restart
echo "Done !"
echo

exit 0
