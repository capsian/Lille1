#!/bin/bash

#ServerIP=localhost

#Get an identity for query and invoke
#. ./test_scripts/enroll_API.sh
#. ./test_scripts/channel_API.sh
#. ./test_scripts/install_instantiate_API.sh

nbSeats=100
seat_i=0
seat_owner_i="free"
ORG1_TOKEN=$(cat tokens/ORG1.tok)

for (( i=1; i<=nbSeats; i++ ))
do
  echo
  echo "seat $i: (seat_$i, $seat_owner_i)"
   curl -s -X POST \
    http://$ServerIP:4000/channels/mychannel/chaincodes/mycc \
    -H "authorization: Bearer $ORG1_TOKEN" \
    -H "content-type: application/json" \
    -d '{
  	"peers": ["peer0.org1.fly.com","peer0.org2.fly.com","peer0.org3.fly.com"],
  	"fcn":"addSeat",
  	"args":["seat_'$i'","'$seat_owner_i'"]
  }'
  echo

  if [ "$i" == "20" ] || [ "$i" == "50" ] || [ "$i" == "80" ] || [ "$i" == "99" ]
  then
    echo "GET query chaincode on peer1 of Org1 -- seek for key: seat_"$(($i-5))
    echo
    curl -X GET \
        "http://$ServerIP:4000/channels/mychannel/chaincodes/mycc?peer=peer0.org1.fly.com&fcn=query&args=%5B%22seat_"$(($i-5))"%22%5D" \
        -H "authorization: Bearer $ORG1_TOKEN" \
        -H "content-type: application/json"
    echo
    echo
  fi

done

echo "GET query ChainInfo"
echo
curl -X GET \
  "http://$ServerIP:4000/channels/mychannel?peer=peer0.org3.fly.com" \
  -H "authorization: Bearer $ORG1_TOKEN" \
  -H "content-type: application/json"
echo
echo
