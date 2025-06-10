#ifndef MYUDPSOCKET_H
#define MYUDPSOCKET_H

#include <QHostAddress>
#include <QNetworkDatagram>
#include <QUdpSocket>

class MyUdpSocket : public QUdpSocket
{
    Q_OBJECT
public:
    MyUdpSocket(const quint16 localPort,
                const QHostAddress localAddress,
                const quint16 peerPort,
                const QHostAddress peerAddress);
signals:
    void readySend(const QString message);
    void messageWasRead(const QString message);
public slots:
    void sendMessage(const QString message);
    void readMessage();
};

#endif // MYUDPSOCKET_H
