#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

void PrintVector(const vector<int>& v) {
    for (const auto& n : v) {
        cout << n << ' ';
    }
}

int main()
{
    int n;
    cin >> n;
    vector<int> vec(n);
    for (size_t i = 0; i < n; ++i) {
        vec[i] = n - i;
    }
    do {
        PrintVector(vec);
        cout << endl;
    } while (prev_permutation(begin(vec), end(vec)));
    return 0;
}
