#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <set>

using namespace std;

class RouteManager {
public:
    void AddRoute(const int& start, const int& finish) {
        reachable_lists_[start].insert(finish);
        reachable_lists_[finish].insert(start);
    }
    int FindNearestFinish(int start,  int finish) const {
        int result = abs(start - finish);
        if (reachable_lists_.count(start) < 1) { return result; }
        const set<int>& start_set = reachable_lists_.at(start);
        if (!start_set.empty()) {
            auto it_lower_bound = start_set.lower_bound(finish);
            if (it_lower_bound == start_set.begin()) {
                return min(abs(finish - *it_lower_bound),
                           abs(start - finish));
            }
            if (it_lower_bound == start_set.end()) {
                return min(abs(finish - *prev(it_lower_bound)),
                           abs(start - finish));
            }
            return min(min(abs(finish - *it_lower_bound),
                           abs(finish - *prev(it_lower_bound))),
                           abs(start - finish));
        }
        return result;
    }
private:
    map<int, set<int>> reachable_lists_;
};

int main() {
    RouteManager routes;

    int query_count;
    cin >> query_count;

    for (int query_id = 0; query_id < query_count; ++query_id) {
        string query_type;
        cin >> query_type;
        int start, finish;
        cin >> start >> finish;
        if (query_type == "ADD") {
            routes.AddRoute(start, finish);
        }
        else if (query_type == "GO") {
            cout << routes.FindNearestFinish(start, finish) << "\n";
        }
    }
    return 0;
}
