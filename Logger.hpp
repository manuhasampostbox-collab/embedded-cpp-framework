#pragma once
#include <string>
#include <iostream>
#include <sstream>
#include <ctime>

// Singleton Logger
class Logger {
public:
    static Logger& getInstance() {
        static Logger instance;
        return instance;
    }
    void info(const std::string& msg) {
        std::cout << "[INFO]  " << msg << "\n";
    }
    void warn(const std::string& msg) {
        std::cout << "[WARN]  " << msg << "\n";
    }
    void error(const std::string& msg) {
        std::cout << "[ERROR] " << msg << "\n";
    }
    void alert(const std::string& msg) {
        std::cout << "[ALERT] *** " << msg << " ***\n";
    }
private:
    Logger() = default;
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;
};
