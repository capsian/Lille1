#!/bin/bash

IP_MIDDLEWARE="172.28.100.172"
IP_REDIS="172.28.101.85"

USER="selim"
PASSWORD="selim"

echo "=========================="
echo "Connect: to middleware"
echo "=========================="
curl -c cookie.txt -F "user=selim" -F "password=selim" $IP_MIDDLEWARE/connect
echo

echo "=========================="
echo "Info with token"
echo "=========================="
curl -b cookie.txt $IP_MIDDLEWARE/info
echo

echo "=========================="
echo "Upload file logo.png"
echo "=========================="
curl -b cookie.txt -X PUT -F "filename=logo.png" -F "file=@logo.png" $IP_MIDDLEWARE/files
echo

echo "=========================="
echo "Can't Upload same file (with same name)"
echo "=========================="
curl -b cookie.txt -X PUT -F "filename=logo.png" -F "file=@logo.png" $IP_MIDDLEWARE/files
echo

echo "=========================="
echo "Patch file logo.png (logo_2.png)"
echo "=========================="
curl -b cookie.txt -X PATCH -F "filename=logo.png" -F "file=@logo_2.png" $IP_MIDDLEWARE/files
echo

echo "=========================="
echo "Get files"
echo "=========================="
curl -b cookie.txt -X GET $IP_MIDDLEWARE/files
echo

echo "=========================="
echo "Del non existent file"
echo "=========================="
curl -b cookie.txt -X DELETE -F "filename=notpresent.png" $IP_MIDDLEWARE/files
echo

echo "=========================="
echo "Del file"
echo "=========================="
curl -b cookie.txt -X DELETE -F "filename=logo.png" $IP_MIDDLEWARE/files
echo

echo "=========================="
echo "Get files"
echo "=========================="
curl -b cookie.txt -X GET $IP_MIDDLEWARE/files
echo