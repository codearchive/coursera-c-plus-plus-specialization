#include <iostream>
#include <map>
#include <exception>
#include <string>

using namespace std;

template <typename Key, typename Value> Value& GetRefStrict(map<Key, Value>& m, const Key& k);

template <typename Key, typename Value>
Value& GetRefStrict(map<Key, Value>& m, const Key& k)
{
    if (m.count(k) == 0)
    {
        throw runtime_error("Element with this key does not exist");
    }
    return m.at(k);
}

int main()
{
    map<int, string> m = { {0, "value"} };
    string& item = GetRefStrict(m, 0);
    item = "newvalue";
    cout << m[0] << endl;
    return 0;
}
