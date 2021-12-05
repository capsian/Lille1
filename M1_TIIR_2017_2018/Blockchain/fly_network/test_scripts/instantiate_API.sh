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

##############
# INSTANTIATE
##############

echo "POST instantiate chaincode on peer1 of Org1"
echo
curl -s -X POST \
  http://$ServerIP:4000/channels/mychannel/chaincodes \
  -H "authorization: Bearer $ORG1_TOKEN" \
  -H "content-type: application/json" \
  -d "{
	\"chaincodeName\":\"mycc\",
	\"chaincodeVersion\":\"v0\",
	\"chaincodeType\": \"$LANGUAGE\",
	\"args\":[\"nbSeat\",\"100\"]
}"
echo
echo

echo "Total execution time : $(($(date +%s)-starttime)) secs ..."
