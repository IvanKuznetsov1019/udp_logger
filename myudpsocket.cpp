#include "myudpsocket.h"

MyUdpSocket::MyUdpSocket(quint16 localPort,
                         QHostAddress localAddress,
                         quint16 peerPort,
                         QHostAddress peerAddress)
{
    setLocalPort(localPort);
    setLocalAddress(localAddress);
    setPeerPort(peerPort);
    setPeerAddress(peerAddress);
    bind(localAddress, localPort);
    connect(this, &MyUdpSocket::readySend, this, &MyUdpSocket::sendMessage);
    connect(this, &MyUdpSocket::readyRead, this, &MyUdpSocket::readMessage);
}

void MyUdpSocket::sendMessage(QString message)
{
    writeDatagram(message.toUtf8(), peerAddress(), peerPort());
}

void MyUdpSocket::readMessage()
{
    QNetworkDatagram datagram = receiveDatagram(1024);
    QByteArray message = datagram.data();
    emit messageWasRead((QString) message);
    //close();
    //-для теста "onStateChanged()"
}
