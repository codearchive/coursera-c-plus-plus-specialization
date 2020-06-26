#pragma once
#include <iostream>
#include <string>
#include <sstream>

class Logger {
public:
    explicit Logger(std::ostream& output_stream) : os(output_stream) {}

    void SetLogLine(bool value) { log_line = value; }
    void SetLogFile(bool value) { log_file = value; }

    void SetLine(const int& line) { line_ = line; }
    void SetFile(const std::string& file) { file_ = file; }

    void Log(const std::string& message);

private:
    std::ostream& os;
    bool log_line = false;
    bool log_file = false;
    std::string file_;
    int line_;
};

#define LOG(logger, message) \
    logger.SetLine(__LINE__); \
    logger.SetFile(__FILE__); \
    logger.Log(message);
