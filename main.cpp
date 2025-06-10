#include <QDebug>
#include <QGuiApplication>
#include <QIcon>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickStyle>
#include <QWindow>

#include "myudpsocket.h"

#define LOCAL_PORT 11111
#define PEER_PORT 22222

int main(int argc, char *argv[])
{
    QQuickStyle::setStyle("Universal");
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    MyUdpSocket sender(LOCAL_PORT, QHostAddress::LocalHost, PEER_PORT, QHostAddress::LocalHost);
    MyUdpSocket receiver(PEER_PORT, QHostAddress::LocalHost, LOCAL_PORT, QHostAddress::LocalHost);
    engine.rootContext()->setContextProperty("sender", &sender);
    engine.rootContext()->setContextProperty("receiver", &receiver);
    app.setWindowIcon(QIcon("D:/logger/images/appIcon.svg"));
    engine.loadFromModule("logger", "Main");
    return app.exec();
}
