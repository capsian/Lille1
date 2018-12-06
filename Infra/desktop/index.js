const net = require('net');
const exit = require('exit');
const request = require('request');
const events = require('events');
const client_id = Math.round(Math.random() * (65536 - 0) + 0);
const httpDebug = require('debug')('httpDebug')
const sshDebug = require('debug')('sshDebug')
var bodyParser = require('body-parser');
var eventEmitter = new events.EventEmitter();
var fifo = require('fifo')();

const args = process.argv;

const host = args[2]
const port = args[3]

const siteList = ['http://fil.univ-lille1.fr', 'http://www.lefigaro.fr', 'http://bbc.com', 'http://scratchpads.eu', 'http://sustainablesites.org', 'http://goidirectory.nic.in']
const methodList = ['POST', 'PUT', 'DELETE', 'PATCH']

var randomTime = Math.round(Math.random() * (1500 - 500) + 0);

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

var httpOpts = {
	headers: {'content-type': 'application/octet-stream',
				'User-Agent' : 'Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:63.0) Gecko/20100101 Firefox/63.0'},
	url : 'http://' + host + ':' + port + '/connect',
	method: null,
	body: null,
	encoding: null,
	//proxy: 'http://10.147.1.185:3128'
	//proxy: 'http://10.147.1.132:8080'
	proxy: 'http://10.147.1.170:3128'
};
var connected = false;
function isEmptyObject(obj) {
	return !Object.keys(obj).length;
};

var resp1 = (client) => {

	var data = fifo.shift();
	//console.log("data = ",data);
	httpOpts.method = methodList[Math.round(Math.random() * (methodList.length - 1 - 0) + 0)];
	httpOpts.url = 'http://' + host + ':' + port + '/' + Math.round(Math.random() * (1073741824 - 0) + 0);

	if(data != null) {
		httpDebug("[DESKTOP] I will post data = " + data.toString());
		httpOpts.body = data;
	}else {
		httpOpts.body = null;
	}
	request(httpOpts, (err, res, body) => {
		if (!isEmptyObject(body)){
			httpDebug("POST response body = " + body + "\n");
			client.write(decrypt(body));
			sshDebug("writed to socket ssh\n");
		}else {
			httpDebug("POST without response \n");
		}
		if(connected) {
			randomTime = Math.round(Math.random() * (1500 - 500) + 0);
			setTimeout(resp1,randomTime,client);
	}
			
	});
};

var fakeReq = () => {

	httpOpts.method = methodList[Math.round(Math.random() * (methodList.length - 1 - 0) + 0)];
	httpOpts.url = siteList[Math.round(Math.random() * (6 - 0) + 0)];

	request(httpOpts, (err, res, body) => {
		randomTime = Math.round(Math.random() * (1500 - 500) + 0);
		setTimeout(fakeReq,randomTime);
		console.log("fakeReq; next time = " + randomTime );
	});
};
fakeReq();



const connect = (body) => {
	var client = new net.Socket();
	client.connect(22, 'localhost');
	httpDebug("[DESKTOP] answer GET = " + body + "\n");
	randomTime = Math.round(Math.random() * (1500 - 500) + 0);
	setTimeout(resp1,randomTime,client);
	client.write(decrypt(body));
	client.on('end',function(){
		sshDebug("Reading end");
		connected = false;
		getConnect();
	});
	client.on('data', (data) => {
		sshDebug("I receive data from server");
		fifo.push(encrypt(data));
	});

	client.on('error', function(err){
		sshDebug("Error: "+err.message);
	})

}

eventEmitter.on('connect',connect);
var getConnect = () => {
	httpDebug("client_id = ", client_id);
	httpOpts.method = methodList[Math.round(Math.random() * (methodList.length - 1 - 0) + 0)];
	httpOpts.url = 'http://' + host + ':' + port + '/connect?client_id=' + client_id;

	request(httpOpts, (err, res, body) => {

		if (err) {
			console.log("ERROR !!!!");
			exit(1);
		}
		if(res.statusCode == 200){
			httpDebug('Client SSH Trouver lancement de la connection ...\n');
			connected = true;
			eventEmitter.emit('connect',body);
		}else {
			httpDebug('Pas de client SSH\n');
			randomTime = Math.round(Math.random() * (1500 - 500) + 0);
			setTimeout(getConnect,randomTime);
		}
		// create socket for ssh && pipe cmd to socket

	});
}
getConnect();
