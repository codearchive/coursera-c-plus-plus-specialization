#include "logger.h"

void Logger::Log(const std::string& message) {
    if (log_line && log_file) {
        os << file_ << ":" << line_ << " ";
    }
    else if (log_line) {
        os << "Line " << line_ << " ";
    }
    else if (log_file) {
        os << file_ << " ";
    }
        os << message << "\n";
}
