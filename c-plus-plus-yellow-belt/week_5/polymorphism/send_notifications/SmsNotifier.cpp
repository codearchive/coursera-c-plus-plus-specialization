#include "SmsNotifier.h"

SmsNotifier::SmsNotifier(const std::string& phone_number) : phone_number_(phone_number) {}

void SmsNotifier::Notify(const std::string& message) {
    SendSms(phone_number_, message);
};