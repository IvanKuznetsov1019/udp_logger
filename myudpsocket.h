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
                const QHostAddress peerAddress,
                const QString id);
    ~MyUdpSocket();
signals:
    void readySend(const QString &message);
    void messageWasRead(const QString &message);
    void bytesWrittenMessage(const QString &id, const QString &message);
    void stateChangedMessage(const QString &id, const QString &message);
    void errorOccurredMessage(const QString &id, const QString &message);
    void readyReadMessage(const QString &id, const QString &message);
public slots:
    void readMessage();
    void sendMessage(const QString &message);
    void slotBytesWrittenToMessage(const qint64 bytes);
    void slotStateChangeToMessage(const SocketState state);
    void slotErrorOccurrenceToMessage(const SocketError err);
    void slotReadyReadToMessage();

private:
    const QString name;
};

#endif // MYUDPSOCKET_H
