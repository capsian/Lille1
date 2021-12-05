#!/bin/bash

starttime=$(date +%s)

# Language defaults to "golang"
#LANGUAGE="golang"
LANGUAGE="node"

ServerIP=10.201.0.47
#ServerIP=localhost

ORG1_TOKEN=$(cat tokens/ORG1.tok)
ORG2_TOKEN=$(cat tokens/ORG2.tok)
ORG3_TOKEN=$(cat tokens/ORG3.tok)

echo "GET query chaincode on peer1 of Org1"
echo
curl -X GET \
  "http://$ServerIP:4000/channels/mychannel/chaincodes/mycc?peer=peer0.org1.fly.com&fcn=query&args=%5B%22nbSeat%22%5D" \
  -H "authorization: Bearer $ORG1_TOKEN" \
  -H "content-type: application/json"
echo
echo

echo "GET query chaincode on peer1 of Org1"
echo
curl -X GET \
  "http://$ServerIP:4000/channels/mychannel/chaincodes/mycc?peer=peer0.org1.fly.com&fcn=query&args=%5B%22seat_0%22%5D" \
  -H "authorization: Bearer $ORG1_TOKEN" \
  -H "content-type: application/json"
echo
echo

echo "POST invoke chaincode on peers of Org1 -- ADD JULIA"
echo
TRX_ID=$(curl -s -X POST \
  http://$ServerIP:4000/channels/mychannel/chaincodes/mycc \
  -H "authorization: Bearer $ORG1_TOKEN" \
  -H "content-type: application/json" \
  -d '{
	"peers": ["peer0.org1.fly.com","peer0.org2.fly.com","peer0.org3.fly.com"],
	"fcn":"addSeat",
	"args":["seat_0","Julia"]
}')
echo "Transacton ID is $TRX_ID"
echo
echo

echo "GET query chaincode on peer1 of Org1"
echo
curl -X GET \
  "http://$ServerIP:4000/channels/mychannel/chaincodes/mycc?peer=peer0.org1.fly.com&fcn=query&args=%5B%22nbSeat%22%5D" \
  -H "authorization: Bearer $ORG1_TOKEN" \
  -H "content-type: application/json"
echo
echo

echo "GET query chaincode on peer1 of Org1"
echo
curl -X GET \
  "http://$ServerIP:4000/channels/mychannel/chaincodes/mycc?peer=peer0.org1.fly.com&fcn=query&args=%5B%22seat_0%22%5D" \
  -H "authorization: Bearer $ORG1_TOKEN" \
  -H "content-type: application/json"
echo
echo

echo "GET query Block by blockNumber"
echo
curl -s -X GET \
  "http://$ServerIP:4000/channels/mychannel/blocks/1?peer=peer0.org1.fly.com" \
  -H "authorization: Bearer $ORG1_TOKEN" \
  -H "content-type: application/json"
echo
echo

echo "GET query Transaction by TransactionID"
echo
curl -s -X GET http://$ServerIP:4000/channels/mychannel/transactions/$TRX_ID?peer=peer0.org1.fly.com \
  -H "authorization: Bearer $ORG1_TOKEN" \
  -H "content-type: application/json"
echo
echo

############################################################################
### TODO: What to pass to fetch the Block information
############################################################################
#echo "GET query Block by Hash"
#echo
#hash=????
#curl -s -X GET \
#  "http://$ServerIP:4000/channels/mychannel/blocks?hash=$hash&peer=peer1" \
#  -H "authorization: Bearer $ORG1_TOKEN" \
#  -H "cache-control: no-cache" \
#  -H "content-type: application/json" \
#  -H "x-access-token: $ORG1_TOKEN"
#echo
#echo

echo "GET query ChainInfo"
echo
curl -s -X GET \
  "http://$ServerIP:4000/channels/mychannel?peer=peer0.org1.fly.com" \
  -H "authorization: Bearer $ORG1_TOKEN" \
  -H "content-type: application/json"
echo
echo

echo "GET query Installed chaincodes"
echo
curl -s -X GET \
  "http://$ServerIP:4000/chaincodes?peer=peer0.org1.fly.com" \
  -H "authorization: Bearer $ORG1_TOKEN" \
  -H "content-type: application/json"
echo
echo

echo "GET query Instantiated chaincodes"
echo
curl -s -X GET \
  "http://$ServerIP:4000/channels/mychannel/chaincodes?peer=peer0.org1.fly.com" \
  -H "authorization: Bearer $ORG1_TOKEN" \
  -H "content-type: application/json"
echo
echo

echo "GET query Channels"
echo
curl -s -X GET \
  "http://$ServerIP:4000/channels?peer=peer0.org1.fly.com" \
  -H "authorization: Bearer $ORG1_TOKEN" \
  -H "content-type: application/json"
echo
echo


echo "Total execution time : $(($(date +%s)-starttime)) secs ..."
