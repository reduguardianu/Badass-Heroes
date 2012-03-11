#ifndef ILOGGER_H__
#define ILOGGER_H__
#include <string>

class ILogger {
public:
    virtual void CriticalError(const std::string&) = 0;
    virtual void Error(const std::string&) = 0;
    virtual void Warning(const std::string&) = 0;
    virtual void Info(const std::string&) = 0;
    virtual void Debug(const std::string&) = 0;
};

#endif
