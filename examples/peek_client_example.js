var PORT = 443;
var HOST = 'localhost';
var tls = require('tls');
var fs = require('fs');

var options = { ca: [ fs.readFileSync('./peek-example-cert.pem') ] };
var client = tls.connect(PORT, HOST, options, function() {
    if (client.authorized) {
        console.log('CONNECTED AND AUTHORIZED\n');
        
        client.on('close', function() {
            console.log('SOCKET CLOSED\n');
            process.exit();
        });

        // Time to make some request to the server
        client.write('GET /hey HTTP/1.1\r\n');
        client.write('\r\n');
    }
    else {
        console.log('AUTH FAILED\n');
        process.exit();
    }
});
client.setEncoding('utf8');
client.on('data', function(data) {
    console.log('-------------');
    console.log(data);
});