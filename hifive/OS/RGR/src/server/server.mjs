import express from 'express';
import http from 'http';
import { Server } from 'socket.io';
import { fileURLToPath } from 'url';
import { dirname } from 'path';
import SIGNALS from '../constants/index.mjs';

const nameOfDir = dirname(fileURLToPath(import.meta.url));
const app = express();
const server = http.createServer(app);
const io = new Server(server);

const clientsById = {};
const clientsIds = [];

function sendMessageToAllClients (clientsIds, message) {
  for (let id of clientsIds) {
    io.to(id).emit(SIGNALS.SERVER_SEND_MESSAGE,message);
  }
}

app.get('/', (request, response) => {
  response.sendFile(`${nameOfDir}/server.html`);
});

io.on('connection', (socket) => {
  console.log(`Client on socket id ${socket.id} connected.`);
  socket.emit(SIGNALS.SERVER_SEND_MESSAGE, 'Now you can start chatting:');

  socket.on(SIGNALS.CLIENT_SEND_MESSAGE, (message) => {
    console.log(`${clientsById[socket.id]}:  ${message}`);
    sendMessageToAllClients(clientsIds, `${clientsById[socket.id]}:  ${message}`);
  });

  socket.on(SIGNALS.CLIENT_CHANGE_NAME, (clientName) => {
    clientsById[socket.id] = clientName;
    clientsIds.push(socket.id);
  });
  
  socket.on(SIGNALS.CLIENT_CLOSE_CONNECTION, () => {
    const disconnectedUserMessage = `${clientsById[socket.id]} disconnected.`;

    delete clientsById[socket.id];
    delete clientsIds[socket.id];

    console.log(`Client ${disconnectedUserMessage}`);
    sendMessageToAllClients(clientsIds, disconnectedUserMessage);
  });
});

server.listen(3000, () => {
  console.log('Server started.');
});

export default io;
