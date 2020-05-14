#pragma once
#include "INotifier.h"
#include <string>

class SmsNotifier : public INotifier {
public:
    SmsNotifier(const std::string& phone_number);
    void Notify(const std::string& message);
private:
    std::string phone_number_;
};