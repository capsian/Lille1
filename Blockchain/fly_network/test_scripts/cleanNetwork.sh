#!/bin/bash

docker rm -f $(docker ps -aq)
docker rmi -f $(docker images | grep dev | awk '{print $3}')
rm -rf fabric-client-kv-org*
rm -rf /tmp/fabric-client-kv-org*
rm -rf tokens