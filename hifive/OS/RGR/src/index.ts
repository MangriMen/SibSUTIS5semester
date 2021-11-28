import { io } from 'socket.io-client';
import sendIcon from '../assets/send.png';
// @ts-ignore
import SIGNALS from './constants/index.mjs';
import {
  QMainWindow,
  QWidget,
  QLabel,
  QBoxLayout,
  QPushButton,
  QIcon,
  Direction,
  QLineEdit,
  QTextEdit,
  WidgetEventTypes,
} from '@nodegui/nodegui';

function handleTextInput () {
  if (messageInput.text().trim() !== '') {
    if (isNameSet) {
        socket.emit(SIGNALS.CLIENT_SEND_MESSAGE, messageInput.text());
    } else {
        socket.emit(SIGNALS.CLIENT_CHANGE_NAME, messageInput.text().trim());
        labelInfo.setText(`${messageInput.text()}:`);
        isNameSet = true;
        socket.connect();
        chatArea.show();
    }
    messageInput.clear();
  }
}

const socket = io('http://localhost:3000');
socket.disconnect();
const win = new QMainWindow();
win.setWindowTitle("SocketChat");
win.setFixedSize(250, 500);
win.addEventListener(WidgetEventTypes.Close, () => {
  socket.emit(SIGNALS.CLIENT_CLOSE_CONNECTION);
})

let isNameSet = false;

socket.on(SIGNALS.SERVER_SEND_MESSAGE, (message: string) => {
  console.log(message);
});

socket.on(SIGNALS.SERVER_CLOSE_CONNECTION, (reason: string) => {
  console.log(`Connection is closed due to ${reason}.`);
});

const centralWidget = new QWidget();
centralWidget.setObjectName("myroot");

const showChatLayout = new QBoxLayout(Direction.TopToBottom);
const labelInfo = new QLabel();
labelInfo.setObjectName("labelInfo");
labelInfo.setText("Your name:");
const chatArea = new QTextEdit();
socket.on(SIGNALS.SERVER_SEND_MESSAGE, (message: string) => {
  chatArea.append(`${message}\n`);
});
chatArea.hide();
chatArea.setReadOnly(true);
showChatLayout.addWidget(labelInfo);
showChatLayout.addWidget(chatArea);

const sendMessageLayout = new QBoxLayout(Direction.LeftToRight);
const messageInput = new QLineEdit();
messageInput.addEventListener('editingFinished', handleTextInput);
const button = new QPushButton();
button.setIcon(new QIcon(sendIcon));
button.addEventListener('clicked', handleTextInput);
sendMessageLayout.addWidget(messageInput);
sendMessageLayout.addWidget(button);

const rootLayout = new QBoxLayout(Direction.TopToBottom);
centralWidget.setLayout(rootLayout);
rootLayout.addLayout(showChatLayout);
rootLayout.addLayout(sendMessageLayout);

win.setCentralWidget(centralWidget);
win.setStyleSheet(
  `
  #myroot {
    background-color: #3A1F32;
    height: '100%';
    justify-content: 'center';
  }
  #labelInfo {
    font-size: 32px;
    font-weight: bold;
    color: white;
    padding: 8px 0;
  }
  `
);
win.show();

(global as any).win = win;
