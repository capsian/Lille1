#!/usr/bin/env bash

function start(){
  userA_id=$1
  if [ -f user/$userA_id/$2.key ]; then
    userA_key=$(cat user/$userA_id/$2.key)
    userB_id=$3
    if [ -f user/$userB_id/$4.key ]; then
        userB_key=$(cat user/$userB_id/$4.key)
        echo "start $userA_id $userA_key $userB_id $userB_key"
    else
      echo "[POC] Key not found for $3" >&2
    fi
    else
      echo "[POC] Key not found for $1" >&2
  fi



}

function add_user() {
  userA_id=$1
  if [ -f user/$userA_id/$2.key ]; then
    userA_key=$(cat user/$userA_id/$2.key)
    userB_id=$3
    if [ -f user/$userB_id/$4.key ]; then
        userB_key=$(cat user/$userB_id/$4.key)
        echo "add_user $userA_id $userA_key $userB_id $userB_key $5 $6"
    else
      echo "[POC] Key not found for $3" >&2
    fi
    else
      echo "[POC] Key not found for $1" >&2
  fi
}

function rm_user() {
  userA_id=$1
  if [ -f user/$userA_id/$2.key ]; then
    userA_key=$(cat user/$userA_id/$2.key)
    userB_id=$3
    if [ -f user/$userB_id/$4.key ]; then
        userB_key=$(cat user/$userB_id/$4.key)
        echo "rm_user $userA_id $userA_key $userB_id $userB_key $5"
    else
      echo "[POC] Key not found for $3" >&2
    fi
    else
      echo "[POC] Key not found for $1" >&2
  fi
}

continue=true;
while $continue; do
  if read -a line
  then
    if [ "${line[0]}" == "start" ] && [ "${#line[@]}" -ge 5 ]
    then
      echo "[POC] Start " "${line[1]}" "${line[2]}" "${line[3]}" "${line[4]}" >&2
      start "${line[1]}" "${line[2]}" "${line[3]}" "${line[4]}"
      sleep 1 >&2
      echo ">" >&2
    elif [ "${line[0]}" == "add" ] && [ "${#line[@]}" -ge 3 ]
    then
      echo "[POC] adding " "${line[1]}" "${line[2]}" >&2
      echo "add" "${line[1]}" "${line[2]}"
      sleep 1 >&2
      echo ">" >&2
    elif [ "${line[0]}" == "add_user" ] && [ "${#line[@]}" -ge 7 ]
    then
      echo "[POC] adding user " "${line[1]}" "${line[2]}" "${line[3]}" "${line[4]}" "${line[5]}" "${line[6]}">&2
      add_user "${line[1]}" "${line[2]}" "${line[3]}" "${line[4]}" "${line[5]}" "${line[6]}"
      sleep 1 >&2
      echo ">" >&2
    elif [ "${line[0]}" == "rm_user" ] && [ "${#line[@]}" -ge 6 ]
    then
      echo "[POC] adding user " "${line[1]}" "${line[2]}" "${line[3]}" "${line[4]}" "${line[5]}" >&2
      rm_user "${line[1]}" "${line[2]}" "${line[3]}" "${line[4]}" "${line[5]}"
      sleep 1 >&2
      echo ">" >&2
    elif [ "${line[0]}" == "get" ] && [ "${#line[@]}" -ge 2 ]
    then
      echo "get in progress" >&2
      echo "get" "${line[1]}"
      sleep 1 >&2
      echo "> " >&2
    elif [ "${line[0]}" == "exit" ]
    then
      echo "Poc exit ..." >&2
      echo "exit"
      continue=false;
    else
    echo "> " >&2
    fi
  fi
done
