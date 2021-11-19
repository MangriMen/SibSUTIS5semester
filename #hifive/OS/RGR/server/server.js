const express = require('express');

const app = express();
const server = require('http').createServer(app);
// eslint-disable-next-line no-unused-vars
const io = require('socket.io')(server);

app.get('/', (request, response) => {
  response.sendFile(`${__dirname}/server.html`);
});

server.listen(3000, () => {
// eslint-disable-next-line no-console
  console.log('server started');
});
