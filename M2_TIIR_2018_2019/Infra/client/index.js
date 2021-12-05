const { exec } = require('child_process');
const express = require('express');
const net = require('net');
const events = require('events');
var bodyParser = require('body-parser');
const httpDebug = require('debug')('httpDebug')
const sshDebug = require('debug')('sshDebug')

var crypto = require('crypto'),
    algorithm = 'aes-256-ctr',
    password = 'xmC6n6MBM3wWEAPQ';

function encrypt(buffer){
  var cipher = crypto.createCipher(algorithm,password)
  var crypted = Buffer.concat([cipher.update(buffer),cipher.final()]);
  return crypted;
}
 
function decrypt(buffer){
  var decipher = crypto.createDecipher(algorithm,password)
  var dec = Buffer.concat([decipher.update(buffer) , decipher.final()]);
  return dec;
}

function isEmptyObject(obj) {
  return !Object.keys(obj).length;
};

const app = express();
const portApp = 80;
app.use(bodyParser.raw({ type: 'application/octet-stream' }))

var eventEmitter = new events.EventEmitter();
var FifoData = require('fifo')();
var client = null;
// SSH Server
const sshServer = net.createServer((c) => {
  client = c;
  // 'connection' listener
  sshDebug('[sshServer] client connected .... ');
  //c.pipe(c);
  c.on('end', () => {
  	sshDebug('client disconnected');
    client=null;
    eventEmitter.removeListener('write', callback);
  });

  c.on('data', (data) => {
    /* Emit event + encrypt data */

    FifoData.push(encrypt(data));
  	sshDebug("[sshServer] i catched data, data = "  +data + "\n");
  });

  const callback = (data) => {
    /* Emit event + decrypt */
    sshDebug("[sshServer] i write data, on ssh Socket data = " + data.toString() + "\n");
    c.write(decrypt(data));
  };
  eventEmitter.on('write', callback);
});

sshServer.on('error', (err) => {
	throw err;
});

sshServer.listen(2222, () => {
  sshDebug('SSH server bound');
});

// Web Server
app.get('/connect', (req, res) => {
  httpDebug("client_id  = ", req.query.client_id);
  if(client == null){
    res.status(400);
    res.end();
  }else {
    var data = FifoData.shift();
    res.status(200);
    if (data == null){
      res.end();
    }else {
      res.send(data);
    }
  }
});

app.post("/cmd", (req,res) => {
  httpDebug("client_id  = ", req.query.client_id);
  if (!isEmptyObject(req.body)){
    httpDebug("POST with body send it to socket ... \n");
    eventEmitter.emit('write', req.body);
    httpDebug("[CLIENT] app.post/cmd, request data = " + req.body + "\n");
  }else {
    httpDebug("[CLIENT] app.post/cmd, no request data \n");
  }

  var data = FifoData.shift();
  if (data == null){
    res.end();
  }else {
    res.send(data);
  }

});

app.listen(portApp, () => httpDebug(`Example app listening on port ${portApp}!`))
