#include <iostream>
#include <vector>
#include <map>

using namespace std;

template <typename T> T Sqr(const T& n);
template <typename T> vector<T> Sqr(const vector<T>& v);
template <typename First, typename Second> pair<First, Second> Sqr(const pair<First, Second>& p);
template <typename First, typename Second> map<First, Second> Sqr(const map<First, Second>& m);

template <typename T> 
T Sqr(const T& n)
{
    return n * n;
}

template <typename T>
vector<T> Sqr(const vector<T>& v)
{
    vector<T> result;
    for (const auto& current_el : v)
    {
        result.push_back(Sqr(current_el));
    }
    return result;
}

template <typename First, typename Second>
pair<First, Second> Sqr(const pair<First, Second>& p)
{
    return pair<First, Second>(Sqr(p.first), Sqr(p.second));
}

template <typename Key, typename Value>
map<Key, Value> Sqr(const map<Key, Value>& m)
{
    map<Key, Value> result;
    for (const auto& p : m)
    {
        result[p.first] = Sqr(p.second);
    }
    return result;
}

int main()
{
    vector<int> v = { 1, 2, 3 };
    cout << "vector:";
    for (int x : Sqr(v)) {
        cout << ' ' << x;
    }
    cout << endl;

    map<int, pair<int, int>> map_of_pairs = {
      {4, {2, 2}},
      {7, {4, 3}}
    };
    cout << "map of pairs:" << endl;
    for (const auto& x : Sqr(map_of_pairs)) {
        cout << x.first << ' ' << x.second.first << ' ' << x.second.second << endl;
    }

    vector<map<int, vector<double>>> it = { { { 2, { 3, 4, 5, 6.8 } } }, { { 5, { 6, 7, 0.01 } } } };
    auto s = Sqr(it);

    return 0;
}
