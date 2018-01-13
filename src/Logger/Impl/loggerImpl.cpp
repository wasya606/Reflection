#include "loggerImpl.h"

LoggerImpl* LoggerImpl::instance = nullptr;

LoggerImpl::LoggerImpl() : logLevel(LoggingFlags::INFO){}

void LoggerImpl::printHeader(const char *functionInfo)
{
    print("\n");

    print(getLevelName(logLevel));
    print(": ");
    if (functionInfo != nullptr)
    {
        print("\"");
        print(functionInfo);
        print("\" says: ");
    }

}

LoggerImpl::~LoggerImpl()
{
    print("Logger is shut down.\n");
}

LoggerImpl *LoggerImpl::getInstance(const SettingsFlags level)
{
    if (instance == nullptr)
    {
        instance = new LoggerImpl();
    }
    instance->logLevel = level;
    return instance;
}

const char *LoggerImpl::getLevelName(SettingsFlags level)
{
    switch (level)
    {
    case LoggingFlags::ERROR:
        return "ERROR";
        break;
    case LoggingFlags::WARNING:
            return "WARNING";
            break;
        case LoggingFlags::INFO:
            return "INFO";
            break;
        case LoggingFlags::DEBUG:
            return "DEBUG";
            break;
        default:
            return nullptr;
            break;
    }
}
