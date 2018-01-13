#ifndef LOGGER_H
#define LOGGER_H
#include "src/Logger/Impl/loggerImpl.h"

class Logger
{
public:
    Logger() = delete;

    static LoggerImpl& error(const char* functionInfo = nullptr)
    {
        return getLogger(LoggingFlags::ERROR, functionInfo);
    }

    static LoggerImpl& warning(const char* functionInfo = nullptr)
    {
        return getLogger(LoggingFlags::WARNING, functionInfo);
    }

    static LoggerImpl& info(const char* functionInfo = nullptr)
    {
        return getLogger(LoggingFlags::INFO, functionInfo);
    }

    static LoggerImpl& debug(const char* functionInfo = nullptr)
    {
        return getLogger(LoggingFlags::DEBUG, functionInfo);
    }

private:
    static LoggerImpl& getLogger(const SettingsFlags level, const char* functionInfo = nullptr)
    {
        LoggerImpl* impl = LoggerImpl::getInstance(level);
        impl->printHeader(functionInfo);
        return *impl;
    }
};


#endif // LOGGER_H
