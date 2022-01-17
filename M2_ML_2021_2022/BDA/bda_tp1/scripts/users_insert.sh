#!/bin/bash

remote_ip="172.28.100.140"

OLDIFS="$IFS"       # Sauvegarde la variable d'environement $IFS. (Voire help read)
IFS=$(echo -e '\t') # Choisi les tabulation comme séparateur.

while read name password; do
  echo "Insert $name $password"
  echo "SELECT create_user('$name', '$password')" | psql -d microblog -U common_user -h $remote_ip -t >/dev/null &
done <users

IFS="$OLDIFS"
wait $(jobs -p)
echo
echo "#Done#"

exit 0
