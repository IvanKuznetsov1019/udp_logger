#include "myudpsocket.h"
#include "logger.h"

MyUdpSocket::MyUdpSocket(const quint16 localPort,
                         const QHostAddress localAddress,
                         const quint16 peerPort,
                         const QHostAddress peerAddress,
                         const QString id)
    : name(id)
{
    setLocalPort(localPort);
    setLocalAddress(localAddress);
    setPeerPort(peerPort);
    setPeerAddress(peerAddress);
    bind(localAddress, localPort);

    connect(this, &MyUdpSocket::readySend, this, &MyUdpSocket::sendMessage);
    connect(this, &MyUdpSocket::readyRead, this, &MyUdpSocket::readMessage);

    connect(this, &MyUdpSocket::stateChanged, this, &MyUdpSocket::slotStateChangeToMessage);
    connect(this, &MyUdpSocket::stateChangedMessage, Logger::instance(), &Logger::eventDetected);

    connect(this, &MyUdpSocket::errorOccurred, this, &MyUdpSocket::slotErrorOccurrenceToMessage);
    connect(this, &MyUdpSocket::errorOccurredMessage, Logger::instance(), &Logger::eventDetected);

    connect(this, &MyUdpSocket::bytesWritten, this, &MyUdpSocket::slotBytesWrittenToMessage);
    connect(this, &MyUdpSocket::bytesWrittenMessage, Logger::instance(), &Logger::eventDetected);

    connect(this, &MyUdpSocket::readyRead, this, &MyUdpSocket::slotReadyReadToMessage);
    connect(this, &MyUdpSocket::readyReadMessage, Logger::instance(), &Logger::eventDetected);
}

MyUdpSocket::~MyUdpSocket()
{
    disconnect();
}

void MyUdpSocket::slotReadyReadToMessage()
{
    emit readyReadMessage(name, "Message was received.");
}

void MyUdpSocket::sendMessage(const QString &message)
{
    writeDatagram(message.toUtf8(), peerAddress(), peerPort());
}

void MyUdpSocket::readMessage()
{
    QNetworkDatagram datagram = receiveDatagram(1024);
    QByteArray message = datagram.data();
    emit messageWasRead((QString) message);
    // close();
    //-для теста "onStateChanged()"
}

void MyUdpSocket::slotBytesWrittenToMessage(const qint64 bytes)
{
    emit bytesWrittenMessage(name, "Message was send (" + QString::number(bytes) + " bytes).");
}

void MyUdpSocket::slotStateChangeToMessage(const SocketState state)
{
    QString message;
    switch (state) {
    case QAbstractSocket::UnconnectedState:
        message = "The socket is not connected.";
        break;
    case QAbstractSocket::HostLookupState:
        message = "The socket is performing a host name lookup.";
        break;
    case QAbstractSocket::ConnectingState:
        message = "The socket has started establishing a connection.";
        break;
    case QAbstractSocket::ConnectedState:
        message = "A connection is established.";
        break;
    case QAbstractSocket::BoundState:
        message = "The socket is bound to an address and port.";
        break;
    case QAbstractSocket::ClosingState:
        message = "The socket is about to close (data may still be waiting to be written).";
        break;
    case QAbstractSocket::ListeningState:
        message = "For internal use only.";
        break;
    default:
        message = "Socket in unknown state.";
        break;
    }
    emit stateChangedMessage(name, message);
}

void MyUdpSocket::slotErrorOccurrenceToMessage(const SocketError err)
{
    QString message;
    switch (err) {
    case QAbstractSocket::ConnectionRefusedError:
        message = "The connection was refused by the peer (or timed out).";
        break;
    case QAbstractSocket::RemoteHostClosedError:
        message = "The remote host closed the connection. Note that the client socket (i.e., this "
                  "socket) will be closed after the remote close notification has been sent.";
        break;
    case QAbstractSocket::HostNotFoundError:
        message = "The host address was not found.";
        break;
    case QAbstractSocket::SocketAccessError:
        message
            = "The socket operation failed because the application lacked the required privileges.";
        break;
    case QAbstractSocket::SocketResourceError:
        message = "The local system ran out of resources (e.g., too many sockets).";
        break;
    case QAbstractSocket::SocketTimeoutError:
        message = "The socket operation timed out.";
        break;
    case QAbstractSocket::DatagramTooLargeError:
        message = "The datagram was larger than the operating system's limit (which can be as low "
                  "as 8192 bytes).";
        break;
    case QAbstractSocket::NetworkError:
        message = "An error occurred with the network (e.g., the network cable was accidentally "
                  "plugged out).";
        break;
    case QAbstractSocket::AddressInUseError:
        message = "The address specified to QAbstractSocket::bind() is already in use and was set "
                  "to be exclusive.";
        break;
    case QAbstractSocket::SocketAddressNotAvailableError:
        message = "The address specified to QAbstractSocket::bind() does not belong to the host.";
        break;
    case QAbstractSocket::UnsupportedSocketOperationError:
        message = "The requested socket operation is not supported by the local operating system "
                  "(e.g., lack of IPv6 support).";
        break;
    case QAbstractSocket::ProxyAuthenticationRequiredError:
        message = "The socket is using a proxy, and the proxy requires authentication.";
        break;
    case QAbstractSocket::SslHandshakeFailedError:
        message = "The SSL/TLS handshake failed, so the connection was closed (only used in "
                  "QSslSocket).";
        break;
    case QAbstractSocket::UnfinishedSocketOperationError:
        message = "Used by QAbstractSocketEngine only, The last operation attempted has not "
                  "finished yet (still in progress in the background).";
        break;
    case QAbstractSocket::ProxyConnectionRefusedError:
        message = "Could not contact the proxy server because the connection to that server was "
                  "denied.";
        break;
    case QAbstractSocket::ProxyConnectionClosedError:
        message = "The connection to the proxy server was closed unexpectedly (before the "
                  "connection to the final peer was established).";
        break;
    case QAbstractSocket::ProxyConnectionTimeoutError:
        message = "The connection to the proxy server timed out or the proxy server stopped "
                  "responding in the authentication phase.";
        break;
    case QAbstractSocket::ProxyNotFoundError:
        message = "The proxy address set with setProxy() (or the application proxy) was not found.";
        break;
    case QAbstractSocket::ProxyProtocolError:
        message = "The connection negotiation with the proxy server failed, because the response "
                  "from the proxy server could not be understood.";
        break;
    case QAbstractSocket::OperationError:
        message
            = "An operation was attempted while the socket was in a state that did not permit it.";
        break;
    case QAbstractSocket::SslInternalError:
        message = "The SSL library being used reported an internal error. This is probably the "
                  "result of a bad installation or misconfiguration of the library.";
        break;
    case QAbstractSocket::SslInvalidUserDataError:
        message = "Invalid data (certificate, key, cypher, etc.) was provided and its use resulted "
                  "in an error in the SSL library.";
        break;
    case QAbstractSocket::TemporaryError:
        message = "A temporary error occurred (e.g., operation would block and socket is "
                  "non-blocking).";
        break;
    case QAbstractSocket::UnknownSocketError:
        message = "An unidentified error occurred.";
        break;
    default:
        message = "Hmm, unknown error state.";
        break;
    }
    emit errorOccurredMessage(name, message);
}
