#!/bin/bash
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

function auth(){
  echo "[Server] Start auth"
  echo "[Server] Search for mask for $1"
  if [ ! -f server/mask/$1.mask ]; then
    echo "Mask not found Abort!"
    KA="0"
  else
    echo -n "[Server] Associate mask and key for user $1 ..."
    maskA=$(cat server/mask/$1.mask)
    KA=$(xor $maskA $2)
    echo "[Server] Done"
  fi

  if [ ! -f server/mask/$3.mask ]; then
    echo "Mask not found Abort!"
    KB="0"
  else
    echo -n "[Server] Associate mask and key for user $3 ..."
    maskB=$(cat server/mask/$3.mask)
    KB=$(xor $maskB $4)
    echo "[Server] Done"
  fi

  echo -n "[Server] Combine the key ..."
  K=$(xor $KA $KB)
  echo $K
  echo "Done"

  echo -n "[Server] Try to unlock the base ..."
  t=$(openssl enc -aes-256-cbc -d -in server/db/auth/auth.enc -k $K -pbkdf2)
  if [[ $? -eq 1 ]]; then
    echo "Wrong KEY"
    return 1
  else
    echo "Done"
    return 0
  fi
}

function start(){
  auth $1 $2 $3 $4
  if [[ $? -eq 1 ]]; then
    start=false
  else
    echo "Service started"
    start=true
  fi
}

function add() {
  if $start ;then
    echo "[Server] Start add data"
    user=$1
    data=$2
    if [ ! -f server/db/data/$user.enc ]; then
      echo $data | openssl enc -aes-256-cbc -out server/db/data/$user.enc -k $K -pbkdf2
    else
      old_data=$(openssl enc -aes-256-cbc -d -in server/db/data/$user.enc -k $K -pbkdf2)
      new_data=$(echo -e "$old_data\n$data" )
      echo $new_data | openssl enc -aes-256-cbc -out server/db/data/$user.enc -k $K -pbkdf2
    fi
    echo "[Server] Start data Added for $user"
  else
    echo "[Server] Service not started"
  fi

}

function get() {
  if $start ;then
    user=$1
    echo "[Server] Start getting data for $user"
    if [ ! -f server/db/data/$user.enc ]; then
      echo "[Server] No data for $user"
    else
      echo "[Server] Data for $user : "
      openssl enc -aes-256-cbc -d -in server/db/data/$user.enc -k $K -pbkdf2
    fi
  else
    echo "[Server] Service not started"
  fi

}

function add_user() {
  auth $1 $2 $3 $4
  group=$6
  if [[ $? -eq 0 ]]; then
    echo "[Server] Start to add user"
    masks=$(openssl enc -aes-256-cbc -d -in server/db/auth/auth.enc -k $K -pbkdf2)

    if [[ $group -eq 0 ]]; then
      echo -n "[Server] Generating a mask for $5 in group A ..."
      newMask=$(openssl rand -hex 32)
      echo -n $newMask > server/mask/$5.mask
      echo "Done"

      echo -n "Generating key for $5 in group A ... "
      newKey=$(xor $KA $newMask)
      mkdir user/$5
      echo -n $newKey > user/$5/$5.key
      echo "Done"
      masks=$(echo -e "$masks \n $newMask")
      echo $masks | openssl enc -aes-256-cbc -out server/db/auth/auth.enc -k $K -pbkdf2
    else
      echo -n "[Server] Generating a mask for $5 in group B..."
      newMask=$(openssl rand -hex 32)
      echo -n $newMask > server/mask/$5.mask
      echo "Done"

      echo -n "Generating key for $5 in group B ... "
      newKey=$(xor $KB $newMask)
      mkdir user/$5
      echo -n $newKey > user/$5/$5.key
      echo "Done"
      masks=$(echo -e "$masks \n $newMask")
      echo $masks | openssl enc -aes-256-cbc -out server/db/auth/auth.enc -k $K -pbkdf2
    fi
  else
    echo "[Server] Wrong credentials"
  fi
}

function rm_user() {
  auth $1 $2 $3 $4
  if [[ $? -eq 0 ]]; then
    echo -n "[Server] Start to rm user $5 ..."
    masks=$(openssl enc -aes-256-cbc -d -in server/db/auth/auth.enc -k $K -pbkdf2)
    rm server/mask/$5.mask
    echo "Done"
    echo $masks | openssl enc -aes-256-cbc -out server/db/auth/auth.enc -k $K -pbkdf2
  else
    echo "[Server] Wrong credentials"
  fi
}


continue=true;
start=false;
while $continue; do
  if read -a line
  then
    if [ "${line[0]}" == "start" ] && [ "${#line[@]}" -ge 5 ]
    then
      echo "[Server] start " "${line[1]}" "${line[2]}" "${line[3]}" "${line[4]}"
      start "${line[1]}" "${line[2]}" "${line[3]}" "${line[4]}"
    elif  [ "${line[0]}" == "add" ] && [ "${#line[@]}" -ge 3 ]
    then
      echo "[Server] add " "${line[1]}" "${line[2]}"
       add "${line[1]}" "${line[2]}"
    elif [ "${line[0]}" == "add_user" ] && [ "${#line[@]}" -ge 7 ]
     then
       echo "[Server] adding user " "${line[1]}" "${line[2]}" "${line[3]}" "${line[4]}" "${line[5]}" "${line[6]}"  >&2
       add_user "${line[1]}" "${line[2]}" "${line[3]}" "${line[4]}" "${line[5]}" "${line[6]}"
     elif [ "${line[0]}" == "rm_user" ] && [ "${#line[@]}" -ge 6 ]
      then
        echo "[Server] adding user " "${line[1]}" "${line[2]}" "${line[3]}" "${line[4]}" "${line[5]}" >&2
        rm_user "${line[1]}" "${line[2]}" "${line[3]}" "${line[4]}" "${line[5]}"
    elif [ "${line[0]}" == "get" ] && [ "${#line[@]}" -ge 2 ]
    then
       get "${line[1]}"
    elif [ "${line[0]}" == "exit" ]
    then
      echo "Server exit ..."
      continue=false;
    else
      echo "Server wrong command : ${line[0]} !!"
    fi
  fi
done
