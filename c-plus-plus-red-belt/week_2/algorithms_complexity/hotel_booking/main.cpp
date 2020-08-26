#include <iostream>
#include <string>
#include <map>
#include <deque>
#include <set>
#include <algorithm>

using namespace std;

class BookingManager {
public:
    BookingManager() : current_time_(0) {}
    void Book(const int64_t& time, const string& hotel_name,
              const size_t& client_id, const size_t& room_count) {
        current_time_ = time;
        RemoveOldData(hotel_name);
        reservation_[hotel_name].push_back(Booking{time, client_id, room_count});
        rooms_by_hotel_[hotel_name] += room_count;
        clients_by_hotel_[hotel_name].insert(client_id);
    }
    size_t Clients(const string& hotel_name) {
        RemoveOldData(hotel_name);
        return clients_by_hotel_[hotel_name].size();
    }
    size_t Rooms(const string& hotel_name) {
        RemoveOldData(hotel_name);
        return rooms_by_hotel_[hotel_name];
    }

private:
    struct Booking {
        int64_t time;
        size_t client_id;
        size_t room_quantity;
    };

    void RemoveOldData(const string& hotel_name) {
        while (!reservation_[hotel_name].empty() &&
               reservation_[hotel_name].front().time <= current_time_ - 86'400) {
            rooms_by_hotel_[hotel_name] -= reservation_[hotel_name].front().room_quantity;
            clients_by_hotel_[hotel_name].erase(reservation_[hotel_name].front().client_id);
            reservation_[hotel_name].pop_front();
        }
    }

    int64_t current_time_;
    map<string, deque<Booking>> reservation_;
    map<string, size_t> rooms_by_hotel_;
    map<string, set<size_t>> clients_by_hotel_;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    BookingManager booking_manager;

    size_t query_count;
    cin >> query_count;

    for (size_t q = 0; q < query_count; ++q) {
        string query_type;
        cin >> query_type;
        if (query_type == "BOOK") {
            int64_t time;
            string hotel_name;
            size_t client_id;
            size_t room_count;
            cin >> time >> hotel_name >> client_id >> room_count;
            booking_manager.Book(time, hotel_name, client_id, room_count);
        }
        else if (query_type == "CLIENTS") {
            string hotel_name;
            cin >> hotel_name;
            cout << booking_manager.Clients(hotel_name) << '\n';
        }
        else if (query_type == "ROOMS") {
            string hotel_name;
            cin >> hotel_name;
            cout << booking_manager.Rooms(hotel_name) << '\n';
        }
    }

    return 0;
}
