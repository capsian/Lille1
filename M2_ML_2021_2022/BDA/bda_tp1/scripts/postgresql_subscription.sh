#!/bin/bash

PUBLICATION_DB_IP="172.28.100.140"

#echo "Creating database microblog (with user postgres)"
#sudo -u postgres createdb microblog
#echo "Done !"
#echo
#echo "Import schema"
#cat ./microblog.sql | psql --dbname microblog

echo "Creating subscription on the replica"
echo "CREATE SUBSCRIPTION microblog_sub CONNECTION 'host=$PUBLICATION_DB_IP port=5432 user=replicator password=replicator dbname=microblog' PUBLICATION microblog_pub;" | psql microblog

exit 0
