#pragma once
#include <string>

class Logger {
public:
    static void logInfo(const std::string &msg);
    static void logWarning(const std::string &msg);
    static void logError(const std::string &msg);
};
