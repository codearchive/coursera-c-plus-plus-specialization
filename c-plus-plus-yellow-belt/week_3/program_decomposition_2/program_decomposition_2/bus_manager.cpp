#include "bus_manager.h"

void BusManager::AddBus(const std::string& bus, const std::vector<std::string>& stops) {
    buses_to_stops[bus] = stops;
    for (const std::string& stop : stops) {
        stops_to_buses[stop].push_back(bus);
    }
}

BusesForStopResponse BusManager::GetBusesForStop(const std::string& stop) const {
    BusesForStopResponse buses_for_stop;
    buses_for_stop.stop = stop;
    if (stops_to_buses.count(stop) == 0) {
        return buses_for_stop;
    }
    for (const std::string& bus : stops_to_buses.at(stop)) {
        buses_for_stop.buses.push_back(bus);
    }
    return buses_for_stop;
}

StopsForBusResponse BusManager::GetStopsForBus(const std::string& bus) const {
    StopsForBusResponse stops_for_bus;
    stops_for_bus.bus = bus;
    if (buses_to_stops.count(bus) == 0) {
        return stops_for_bus;
    }
    for (const std::string& stop : buses_to_stops.at(bus)) {
        if (stops_to_buses.at(stop).size() == 1) {
            stops_for_bus.stops.push_back({ stop });
        }
        else {
            std::vector<std::string> buses_for_stop;
            buses_for_stop.push_back(stop);
            for (const std::string& other_bus : stops_to_buses.at(stop)) {
                if (bus != other_bus) {
                    buses_for_stop.push_back(other_bus);
                }
            }
            stops_for_bus.stops.push_back(buses_for_stop);
        }
    }
    return stops_for_bus;
}

AllBusesResponse BusManager::GetAllBuses() const {
    AllBusesResponse all_buses_response;
    all_buses_response.all_buses = buses_to_stops;
    return all_buses_response;
}