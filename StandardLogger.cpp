#include"StandardLogger.h"

const std::string CRITICAL_ERROR = "CRITICAL ERROR";
const std::string ERROR = "ERROR";
const std::string WARNING = "WARNING";
const std::string INFO = "INFO";
const std::string DEBUG = "DEBUG";

void StandardLogger::CriticalError(const std::string& msg) {
    LogToStd(CRITICAL_ERROR, msg, "124", std::cerr);
}

void StandardLogger::Error(const std::string& msg) {
    LogToStd(ERROR, msg, "208", std::cerr);
}

void StandardLogger::Warning(const std::string& msg) {
    LogToStd(WARNING, msg, "226", std::cerr);
}

void StandardLogger::Info(const std::string& msg) {
    LogToStd(INFO, msg, "195", std::cout);
}

void StandardLogger::Debug(const std::string& msg) {
    LogToStd(DEBUG, msg, "87", std::cout);
}

void StandardLogger::LogToStd(const std::string& category, const std::string& msg, const char* color, std::ostream& target) {
    target << "\033[0;38;5;" << color << "m[" << category << "] " << msg << "\033[39m" << std::endl;
}
