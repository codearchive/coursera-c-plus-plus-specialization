#pragma once
#include "INotifier.h"
#include <string>

class EmailNotifier : public INotifier {
public:
    EmailNotifier(const std::string& email);
    void Notify(const std::string& message);
private:
    std::string email_;
};