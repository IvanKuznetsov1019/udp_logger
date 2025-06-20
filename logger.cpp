#include "logger.h"
#include "myudpsocket.h"

Logger::Logger() {}

Logger *Logger::instance()
{
    static Logger logger;
    return &logger;
}
