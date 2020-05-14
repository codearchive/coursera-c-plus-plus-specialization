#include "EmailNotifier.h"
#include "SmsNotifier.h"

#include <iostream>
#include <string>

void Notify(INotifier& notifier, const std::string& message) {
    notifier.Notify(message);
}

int main() {
    SmsNotifier sms{ "+7-495-777-77-77" };
    EmailNotifier email{ "na-derevnyu@dedushke.ru" };

    Notify(sms, "I have White belt in C++");
    Notify(email, "And want a Yellow one");
    return 0;
}