#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;
int main() {
    vector<string> keys = {"a", "b", "c"};
    vector<int> values = {3, 1, 2};

    map<string, int> myMap;
    for (size_t i = 0; i < keys.size(); ++i) {
        myMap[keys[i]] = values[i];
    }

    vector<pair<string, int>> sortedMap(myMap.begin(), myMap.end());
    sort(sortedMap.begin(), sortedMap.end(), [](const auto &a, const auto &b) {
        return a.second < b.second;
    });

    for (const auto &pair : sortedMap) {
        cout << pair.first << ": " << pair.second << endl;
    }

    return 0;
}
