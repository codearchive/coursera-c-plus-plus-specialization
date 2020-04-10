#include <string>
#include <iostream>
#include <vector>
#include <map>

using namespace std;

enum class QueryType {
    NewBus,
    BusesForStop,
    StopsForBus,
    AllBuses
};

struct Query {
    QueryType type;
    string bus;
    string stop;
    vector<string> stops;
};

istream& operator >> (istream& is, Query& q) {
    string query_type;
    is >> query_type;
    if (query_type == "NEW_BUS") {
        q.type = QueryType::NewBus;
        is >> q.bus;
        unsigned stop_count;
        is >> stop_count;
        q.stops.resize(stop_count);
        for (auto& stop : q.stops) {
            is >> stop;
        }
    }
    else if (query_type == "BUSES_FOR_STOP") {
        q.type = QueryType::BusesForStop;
        is >> q.stop;
    }
    else if (query_type == "STOPS_FOR_BUS") {
        q.type = QueryType::StopsForBus;
        is >> q.bus;
    }
    else if (query_type == "ALL_BUSES") {
        q.type = QueryType::AllBuses;
    }
    return is;
}

struct BusesForStopResponse {
    string stop;
    vector<string> buses;
};

ostream& operator << (ostream& os, const BusesForStopResponse& r) {
    if (r.buses.empty()) {
        os << "No stop";
    }
    else {
        for (const auto& bus : r.buses) {
            os << bus << " ";
        }
    }
    return os;
}

struct StopsForBusResponse {
    string bus;
    vector<vector<string>> stops;
};

ostream& operator << (ostream& os, const StopsForBusResponse& r) {
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
            os << endl;
        }
    }
    return os;
}

struct AllBusesResponse {
    map<string, vector<string>> all_buses;
};

ostream& operator << (ostream& os, const AllBusesResponse& r) {
    if (r.all_buses.empty()) {
        os << "No buses";
    }
    for (const auto& bus_item : r.all_buses) {
        os << "Bus " << bus_item.first << ": ";
        for (const string& stop : bus_item.second) {
            os << stop << " ";
        }
        os << endl;
    }
    return os;
}

class BusManager {
public:
    void AddBus(const string& bus, const vector<string>& stops) {
        buses_to_stops[bus] = stops;
        for (const string& stop : stops) {
            stops_to_buses[stop].push_back(bus);
        }
    }

    BusesForStopResponse GetBusesForStop(const string& stop) const {
        BusesForStopResponse buses_for_stop;
        buses_for_stop.stop = stop;
        if (stops_to_buses.count(stop) == 0) {
            return buses_for_stop;
        }
        for (const string& bus : stops_to_buses.at(stop)) {
            buses_for_stop.buses.push_back(bus);
        }
        return buses_for_stop;
    }

    StopsForBusResponse GetStopsForBus(const string& bus) const {
        StopsForBusResponse stops_for_bus;
        stops_for_bus.bus = bus;
        if (buses_to_stops.count(bus) == 0) {
            return stops_for_bus;
        }
        for (const string& stop : buses_to_stops.at(bus)) {
            if (stops_to_buses.at(stop).size() == 1) {
                stops_for_bus.stops.push_back({ stop });
            }
            else {
                vector<string> buses_for_stop;
                buses_for_stop.push_back(stop);
                for (const string& other_bus : stops_to_buses.at(stop)) {
                    if (bus != other_bus) {
                        buses_for_stop.push_back(other_bus);
                    }
                }
                stops_for_bus.stops.push_back(buses_for_stop);
            }
        }
        return stops_for_bus;
    }

    AllBusesResponse GetAllBuses() const {
        AllBusesResponse all_buses_response;
        all_buses_response.all_buses = buses_to_stops;
        return all_buses_response;
    }
private:
    map<string, vector<string>> buses_to_stops, stops_to_buses;
};

int main() {
    int query_count;
    Query q;

    cin >> query_count;

    BusManager bm;
    for (int i = 0; i < query_count; ++i) {
        cin >> q;
        switch (q.type) {
        case QueryType::NewBus:
            bm.AddBus(q.bus, q.stops);
            break;
        case QueryType::BusesForStop:
            cout << bm.GetBusesForStop(q.stop) << endl;
            break;
        case QueryType::StopsForBus:
            cout << bm.GetStopsForBus(q.bus) << endl;
            break;
        case QueryType::AllBuses:
            cout << bm.GetAllBuses() << endl;
            break;
        }
    }

    return 0;
}