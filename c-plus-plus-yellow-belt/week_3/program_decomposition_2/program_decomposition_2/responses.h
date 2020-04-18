#pragma once
#include <string>
#include <vector>
#include <map>

struct BusesForStopResponse {
    std::string stop;
    std::vector<std::string> buses;
};

struct StopsForBusResponse {
    std::string bus;
    std::vector<std::vector<std::string>> stops;
};

struct AllBusesResponse {
    std::map<std::string, std::vector<std::string>> all_buses;
};

std::ostream& operator << (std::ostream& os, const BusesForStopResponse& r);
std::ostream& operator << (std::ostream& os, const StopsForBusResponse& r);
std::ostream& operator << (std::ostream& os, const AllBusesResponse& r);