#!/bin/bash

echo "Cleaning ....."
sudo docker-compose down
sudo docker rmi frontend

echo "Building docker frontend image with Dockerfile"
sudo docker build -t frontend:v1 -t frontend:latest .

echo "Injecting backend URL :"
URL="backend.com"
VERSION="1.0.0"
sed -i -e 's/INJECT_URL/'$URL'/g' docker-compose.yml

echo "Starting containers ...."
sudo docker-compose up -d