#!/usr/bin/env bash

echo
echo " INTERPRETE SH"
echo

dirList=(`ls -X examples/js/`)

for ((i=0; i<${#dirList[@]}; i++)); do
 echo "$(($i +1 )))  ${dirList[$i]}";
done

echo
read -p "choose file : " tmp
file=${dirList[$(($tmp-1))]}

echo "file name: $file"

echo " Lexing, Parsing .... "
`./tools/jsp ./examples/js/$file > output/$file.parse`
echo "DONE ! "

echo "Interpretation .... "
./build/bin/unserializer "./output/$file.parse"
echo "DONE !!"

exit 0