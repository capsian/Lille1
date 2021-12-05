#!/usr/bin/env bash

echo " Testing REST Server"

read -p " Start the FTP Server && REST Server .... (press to continue)" $tmp

echo "Create tmp users dirs ... "
mkdir -p /tmp/toto /tmp/toto/dir1 /tmp/toto/dir2
echo "OK" > /tmp/toto/ok.txt
echo "OK1" > /tmp/toto/dir1/ok1.txt
echo "OK2" > /tmp/toto/dir2/ok2.txt
echo " DONE !"

echo "Create tmp upload ... "
echo "Upload OK" > /tmp/upload.txt
echo " DONE !"

echo ""
echo "Testing CONNECT "
curl -H "user:toto" -H "pass:toto" -X GET http://localhost:8080/ftp/127.0.0.1:2048/
echo ""

echo ""
echo "Testing LIST "
curl -H "user:toto" -H "pass:toto" -X GET http://localhost:8080/ftp/127.0.0.1:2048/list/
echo ""

echo ""
echo "Testing PWD "
curl -H "user:toto" -H "pass:toto" -X GET http://localhost:8080/ftp/127.0.0.1:2048/pwd/
echo ""

echo ""
echo "Testing CWD "
curl -H "user:toto" -H "pass:toto" -X GET http://localhost:8080/ftp/127.0.0.1:2048/cwd/dir1
echo ""

echo ""
echo "Testing CWDUP "
curl -H "user:toto" -H "pass:toto" -X GET http://localhost:8080/ftp/127.0.0.1:2048/cwdup/..
echo ""

echo ""
echo "Testing RETV "
curl -H "user:toto" -H "pass:toto" -X GET http://localhost:8080/ftp/127.0.0.1:2048/retv/tmp/toto/ok.txt > out.retv
echo ""

echo ""
echo "Testing STOR "
curl -H "user:toto" -H "pass:toto" -X POST -F "file=@/tmp/upload.txt" http://localhost:8080/ftp/127.0.0.1:2048/stor/upload.txt
echo ""

exit 0