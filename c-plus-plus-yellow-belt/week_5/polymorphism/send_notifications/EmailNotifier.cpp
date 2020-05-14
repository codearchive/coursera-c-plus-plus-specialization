#include "EmailNotifier.h"

EmailNotifier::EmailNotifier(const std::string& email) : email_(email) {}

void EmailNotifier::Notify(const std::string& message) {
    SendEmail(email_, message);
};