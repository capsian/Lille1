#!/usr/bin/env bash

VERSION="v1"

#echo "Adding your user to Docker group"

sudo docker build -t dev-env:$VERSION .

sudo docker run -v $(pwd):/dev-env -it --rm --name dev_env_$VERSION dev-env:$VERSION /dev-env/docker_entry_point.sh
