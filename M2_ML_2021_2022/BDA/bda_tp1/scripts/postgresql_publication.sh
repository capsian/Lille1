#!/bin/bash

REPLICA_DB_IP="172.28.100.203"

# Master
STR_FIND="#wal_level = replica			# minimal, replica, or logical"
STR_RPLC="wal_level = logical			# minimal, replica, or logical"
echo "Enabling wal_level to logical"
sudo sed -i "s/$STR_FIND/$STR_RPLC/g" /etc/postgresql/13/main/postgresql.conf
echo "Done !"
echo
echo "Check config file"
cat /etc/postgresql/13/main/postgresql.conf | grep wal_level
echo

echo "Update pg_hba.conf to enable replica db to connect (with user root)"
su root -c "echo \"host    all             all		$REPLICA_DB_IP/32		md5\" >>   /etc/postgresql/13/main/pg_hba.conf"
echo "Done !"
echo
echo "Check config file"
sudo tail /etc/postgresql/13/main/pg_hba.conf
echo

echo "Enable communication between the two VM (add firewall rule)"
sudo ufw allow from $REPLICA_DB_IP to any port 5432
echo "Done !"
echo

echo "Restarting postgres service ...."
sudo systemctl restart postgresql
sleep 3
echo "Done !"
echo

echo "Create role replicator with replication permission"
sudo -u postgres psql -c "CREATE ROLE replicator REPLICATION LOGIN PASSWORD 'replicator';"
sudo -u postgres psql -c "GRANT ALL PRIVILEGES ON DATABASE microblog TO replicator;"
sudo -u postgres psql -c "GRANT ALL PRIVILEGES ON ALL TABLES IN SCHEMA public TO replicator;"
echo "Done !"
echo

echo "Creating publication"
echo "CREATE PUBLICATION microblog_pub;" | psql --dbname microblog
echo "ALTER PUBLICATION microblog_pub ADD TABLE user_store,messages_store,followers;" | psql --dbname microblog

exit 0
