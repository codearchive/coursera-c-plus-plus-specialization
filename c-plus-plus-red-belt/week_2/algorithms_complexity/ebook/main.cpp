#include <iomanip>
#include <iostream>
#include <vector>
#include <utility>
#include <map>

using namespace std;

class ReadingManager {
public:
    ReadingManager() {}

    void Read(int user_id, int page_count) {
        const auto [it_insertion, success] = users_.insert({user_id, page_count});
        if (success) {
            ++pages_[page_count];
        }
        else {
            int prev_page = users_[user_id];
            users_[user_id] = page_count;
            ++pages_[page_count];
            --pages_[prev_page];
            if (pages_[prev_page] == 0) pages_.erase(prev_page);
        }
    }

    double Cheer(int user_id) const {
        if (users_.count(user_id) == 0 || (users_.count(user_id) == 1 &&
                                           users_.at(user_id) == 0)) {
            return 0;
        }

        int users = GetUserCount();
        if (users == 1) {
            return 1;
        }

        int persons_read_less = 0;
        int not_read_yet = 0;
        for (auto it = pages_.begin(); it != pages_.lower_bound(users_.at(user_id)); ++it) {
            if (it->first == 0) {
                not_read_yet = it->second;
                continue;
            }
            persons_read_less += it->second;
        }
        return static_cast<double>(persons_read_less) / (users - not_read_yet - 1);
    }

private:
    static const int MAX_USER_COUNT_ = 100'000;

    map<int, int> users_;
    map<int, int> pages_;

    int GetUserCount() const {
        return users_.size();
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ReadingManager manager;

    int query_count;
    cin >> query_count;

    for (int query_id = 0; query_id < query_count; ++query_id) {
        string query_type;
        cin >> query_type;
        int user_id;
        cin >> user_id;

        if (query_type == "READ") {
            int page_count;
            cin >> page_count;
            manager.Read(user_id, page_count);
        } else if (query_type == "CHEER") {
            cout << setprecision(6) << manager.Cheer(user_id) << "\n";
        }
    }

    return 0;
}
