#include "client.h"

extern bool isTourist;
extern QString UserName;

chatClient::chatClient(QObject *parent) : QObject(parent)
{
    this->sock = new QTcpSocket(this);
    connect(sock, SIGNAL(readyRead()), this, SLOT(readMsg()));
}

void chatClient::connectToServer(QString ip, uint16_t port){
    sock->connectToHost(ip, port);
}

void chatClient::sendMessage(QByteArray msg){
    sock->write(msg);
    sock->waitForBytesWritten();
    return;
}

void chatClient::sendMessage(QString msg){
    sendMessage(msg.toUtf8());
}

void chatClient::readMsg(){
    QString receivedMsg = QString::fromUtf8(sock->readAll());
    emit newMessageRead(receivedMsg);
}
chatClient::~chatClient(){
    if(sock != nullptr) delete sock;
}

