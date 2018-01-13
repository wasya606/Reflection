#ifndef LOGGER_IMPL_H
#define LOGGER_IMPL_H
#include "src/Common/common.h"
#include "src/Settings/Interface/settings.h"
#include <iostream>


using namespace Common;

class Logger;

class LoggerImpl
{
    friend class Logger;    
public:
    ~LoggerImpl();

    template<typename T>
    LoggerImpl& operator << (T const & arg)
    {       
        print(arg);
        return *this;
    }
private:

    static LoggerImpl* getInstance(const SettingsFlags level = LoggingFlags::INFO);

    LoggerImpl();

    static const char* getLevelName(const SettingsFlags level);

    void printHeader(const char* functionInfo = nullptr);
    template<typename T>
    inline void print(const T& data)
    {
        //if (Settings::getSettingsFlag(SettingsID::SETTINGS_LOGGING, logLevel) > 0)
        {
            std::cout << data;
        }
    }

private:
    static LoggerImpl* instance;

    SettingsFlags logLevel;
};

#endif // LOGGER_IMPL_H
