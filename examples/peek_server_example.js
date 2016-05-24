var fs = require('fs');
var express = require('express');
var https = require('https');
var peek = require('bindings')('peek.node').peek;

var key = fs.readFileSync('./peek-example-key.pem');
var cert = fs.readFileSync('./peek-example-cert.pem');
var https_options = {
    key: key,
    cert: cert
};
var PORT = 443;
var HOST = 'localhost';
app = express();

server = https.createServer(https_options, function(req, res) {
    res.writeHead(200);
    res.end("Hello");
}).listen(PORT, HOST);

function toHexString(byteArray) {
  return byteArray.map(function(byte) {
    return ('0' + (byte & 0xFF).toString(16)).slice(-2);
  }).join(' ')
}

server.on('connection', function(connection) {
    var buffer = new Buffer(1000);
    var ret = peek(connection._handle.fd, 1000, buffer);
    console.log('New connection, fd: ' + connection._handle.fd + ', ret: ' + ret);
    if (ret > 0) {
        console.log('Returned bytes: ' + buffer.slice(0,ret).toString('hex'));
    }

});
console.log('HTTPS Server listening on %s:%s', HOST, PORT);
