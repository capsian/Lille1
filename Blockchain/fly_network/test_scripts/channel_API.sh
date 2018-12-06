#!/bin/bash

starttime=$(date +%s)

# Language defaults to "golang"
#LANGUAGE="golang"
LANGUAGE="node"

##set chaincode path
function setChaincodePath(){
	LANGUAGE=`echo "$LANGUAGE" | tr '[:upper:]' '[:lower:]'`
	case "$LANGUAGE" in
		"golang")
		CC_SRC_PATH="github.com/example_cc/go"
		;;
		"node")
		CC_SRC_PATH="/home/worker/PJI/fly_network/artifacts/src/github.com/example_cc/node"
		;;
		*) printf "\n ------ Language $LANGUAGE is not supported yet ------\n"$
		exit 1
	esac
}

setChaincodePath


##############
# CREATE
##############
echo
echo "POST request Create channel  ..."
echo
curl -s -X POST \
  http://$ServerIP:4000/channels \
  -H "authorization: Bearer $ORG1_TOKEN" \
  -H "content-type: application/json" \
  -d '{
	"channelName":"mychannel",
	"channelConfigPath":"../artifacts/channel/mychannel.tx"
}'
echo
echo

##############
# JOINGING
##############
echo "POST request Join channel on Org1"
echo
curl -s -X POST \
  http://$ServerIP:4000/channels/mychannel/peers \
  -H "authorization: Bearer $ORG1_TOKEN" \
  -H "content-type: application/json" \
  -d '{
	"peers": ["peer0.org1.fly.com","peer1.org1.fly.com"]
}'
echo
echo

echo "POST request Join channel on Org2"
echo
curl -s -X POST \
  http://$ServerIP:4000/channels/mychannel/peers \
  -H "authorization: Bearer $ORG2_TOKEN" \
  -H "content-type: application/json" \
  -d '{
	"peers": ["peer0.org2.fly.com","peer1.org2.fly.com"]
}'
echo
echo

echo "POST request Join channel on Org3"
echo
curl -s -X POST \
  http://$ServerIP:4000/channels/mychannel/peers \
  -H "authorization: Bearer $ORG3_TOKEN" \
  -H "content-type: application/json" \
  -d '{
	"peers": ["peer0.org3.fly.com","peer1.org3.fly.com"]
}'
echo
echo

echo "Total execution time : $(($(date +%s)-starttime)) secs ..."
