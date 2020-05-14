#pragma once
#include "date.h"

#include <sstream>
#include <string>

struct Entry {
    Date date;
    std::string event;
};

std::ostream& operator<<(std::ostream& os, const Entry& entry);

bool operator==(const Entry& entry, const std::string str);
bool operator!=(const Entry& entry, const std::string str);
