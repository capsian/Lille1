#!/bin/bash

#echo "Cleaning ...."
rm -rf server/
rm -rf user/
mkdir server server/db server/db/data server/mask server/db/auth user

function  xor()
{
	local res=(`echo "$1" | sed "s/../0x& /g"`)
	shift 1
	while [[ "$1" ]]; do
	    local one=(`echo "$1" | sed "s/../0x& /g"`)
	    local count1=${#res[@]}
	    if [ $count1 -lt ${#one[@]} ]
	    then
	          count1=${#one[@]}
	    fi
	    for (( i = 0; i < $count1; i++ ))
	    do
	          res[$i]=$((${one[$i]:-0} ^ ${res[$i]:-0}))
	    done
	    shift 1
	done
	printf "%02x" "${res[@]}"
}

echo -n "Generating K1 : "
K1_hex=$(openssl rand -hex 32)
echo $K1_hex

echo -n "Generating K2 : "
K2_hex=$(openssl rand -hex 32)
echo $K2_hex

echo -n "Generating mask for Alice : "
maskA1_hex=$(openssl rand -hex 32)
echo $maskA1_hex
echo -n $maskA1_hex > server/mask/Alice.mask

echo -n "Generating mask for Bob : "
maskB1_hex=$(openssl rand -hex 32)
echo $maskB1_hex
echo -n $maskB1_hex > server/mask/Bob.mask

echo -n "Generating key for user Alice : "
K1a1_hex=$(xor $K1_hex $maskA1_hex)
echo $K1a1_hex
mkdir user/Alice
echo -n $K1a1_hex > user/Alice/Alice.key


echo -n "Generating key for user Bob : "
K2b1_hex=$(xor $K2_hex $maskB1_hex)
echo $K2b1_hex
mkdir user/Bob
echo -n $K2b1_hex > user/Bob/Bob.key

K_hex=$(xor $K1_hex $K2_hex)

echo -n "Key for DB : "
echo $K_hex

echo "Crypting the DB with K"
echo "123456789" | openssl enc -aes-256-cbc -out server/db/data/toto.enc -k $K_hex -pbkdf2
echo -e "$maskA1 \n $maskA2" | openssl enc -aes-256-cbc -out server/db/auth/auth.enc -k $K_hex -pbkdf2
