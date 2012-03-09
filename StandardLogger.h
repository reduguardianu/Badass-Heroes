#ifndef STANDARD_LOGGER_H__
#define STANDARD_LOGGER_H__

#include <string>
#include <iostream>
#include "ILogger.h"

class StandardLogger:public ILogger {
public:
    void CriticalError(const std::string&);
    void Error(const std::string&);
    void Warning(const std::string&);
    void Info(const std::string&);
    void Debug(const std::string&);
private:
    void LogToStd(const std::string&, const std::string&, const char[8], std::ostream&);
};

#endif
