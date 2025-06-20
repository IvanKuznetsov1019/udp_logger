#ifndef LOGGER_H
#define LOGGER_H

#include <QObject>
#include "myudpsocket.h"

class Logger : public QObject
{
    Q_OBJECT
public:
    static Logger *instance();

private:
    Logger();
    Logger(const Logger &);
signals:
    void eventDetected(const QString &id, const QString &description);
};

#endif // LOGGER_H
