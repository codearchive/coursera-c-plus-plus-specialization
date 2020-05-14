#pragma once
#include <string>
#include <iostream>

class INotifier {
public:
    virtual void Notify(const std::string& message) = 0;
};

inline void SendSms(const std::string& number, const std::string& message) {
    std::cout << "Send '" << message << "' to number " << number << std::endl;
}

inline void SendEmail(const std::string& email, const std::string& message) {
    std::cout << "Send '" << message << "' to e-mail " << email << std::endl;
}
