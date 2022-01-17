#!/bin/bash

remote_ip="172.28.100.140"

echo "Generating user pass combo"
for i in $(seq 0 1000); do
    rig | head -n1 >> names # generate random names
    head -c 100 /dev/urandom | md5sum | cut -f1 -d " " >> pass # generate random passwords
done
paste names pass > users
rm names pass
echo "Done !"
head users
echo

exit 0
