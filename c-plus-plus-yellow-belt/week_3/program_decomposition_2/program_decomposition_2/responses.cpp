#include "responses.h"

std::ostream& operator << (std::ostream& os, const BusesForStopResponse& r) {
    if (r.buses.empty()) {
        os << "No stop";
    } else {
        for (const auto& bus : r.buses) {
            os << bus << " ";
        }
    }
    return os;
}

std::ostream& operator << (std::ostream& os, const StopsForBusResponse& r) {
    if (r.stops.empty()) {
        os << "No bus";
    }
    else {
        for (const auto& stop : r.stops) {
            os << "Stop " << stop[0] << ": ";
            if (stop.size() == 1) {
                os << "no interchange";
            }
            else {
                for (size_t i = 1; i < stop.size(); ++i) {
                    os << stop[i] << " ";
                }
            }
            os << std::endl;
        }
    }
    return os;
}

std::ostream& operator << (std::ostream& os, const AllBusesResponse& r) {
    if (r.all_buses.empty()) {
        os << "No buses";
    }
    for (const auto& bus_item : r.all_buses) {
        os << "Bus " << bus_item.first << ": ";
        for (const std::string& stop : bus_item.second) {
            os << stop << " ";
        }
        os << std::endl;
    }
    return os;
}