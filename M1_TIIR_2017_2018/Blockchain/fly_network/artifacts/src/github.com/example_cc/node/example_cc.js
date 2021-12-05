/*
# Copyright IBM Corp. All Rights Reserved.
#
# SPDX-License-Identifier: Apache-2.0
*/

const shim = require('fabric-shim');
const util = require('util');

var Chaincode = class {

    // Initialize the chaincode
    async Init(stub) {
        console.info('========= example_cc Init =========');

        let ret = stub.getFunctionAndParameters();
        console.info(ret);

        let args = ret.params;
        if (args.length != 2) {
            return shim.error('Incorrect number of arguments. Expecting 2');
        }

        //let key = args[0];
        let nbSeat = args[1];

        if (typeof parseInt(nbSeat) !== 'number') {
            return shim.error('Expecting integer value for asset holding');
        }

        console.info("Init with nbSeat = " + nbSeat);

        try {

            await stub.putState("nbSeat", Buffer.from(nbSeat));
            return shim.success();

        } catch (err) {
            return shim.error(err);
        }
    }

    async Invoke(stub) {
        console.info('========= example_cc Invoke =========');

        let ret = stub.getFunctionAndParameters();
        console.info(ret);

        let method = this[ret.fcn];
        if (!method) {
            console.error('no method of name:' + ret.fcn + ' found');
            return shim.error('no method of name:' + ret.fcn + ' found');
        }

        console.info('\nCalling method : ' + ret.fcn);
        try {
            let payload = await
            method(stub, ret.params);
            return shim.success(payload);
        } catch (err) {
            console.log(err);
            return shim.error(err);
        }
    }

    // Initialize the chaincode
    async addSeat(stub, args) {

        console.info('========= example_cc addSeat =========');

        if (args.length != 2) {
            throw new Error('Incorrect number of arguments. Expecting 2');
        }

        let seatNum   = args[0];
        let seatOwner = args[1];

        console.info("addSeat seatNum: " + seatNum + ", seatOwner: " + seatOwner);

        // Write the states back to the ledger
        await stub.putState(seatNum.toString(), Buffer.from(seatOwner));
    }

    // Deletes an entity from state
    async delete(stub, args) {

        if (args.length != 1) {
            throw new Error('Incorrect number of arguments. Expecting 1');
        }

        let A = args[0];

        // Delete the key from the state in ledger
        await
        stub.deleteState(A);
    }

    // query callback representing the query of a chaincode
    async query(stub, args) {

        console.info('========= example_cc query =========');

        if (args.length != 1) {
            throw new Error('Incorrect number of arguments. Expecting seatNumber')
        }

        let jsonResp = {};
        let seatNumber = args[0];

        // Get the state from the ledger
        let ownerBytes = await stub.getState(seatNumber.toString());
        if (!ownerBytes) {
            jsonResp.error = 'Failed to get state for ' + seatNumber;
            throw new Error(JSON.stringify(jsonResp));
        }

        jsonResp.seatNumber = seatNumber;
        jsonResp.amount = ownerBytes.toString();

        console.info('Query Response:');
        console.info(jsonResp);

        return ownerBytes;
    }
};

shim.start(new Chaincode());
