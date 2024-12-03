#include <iostream>
#include <vector>
#include <limits>
#include <cstdlib>

using namespace std;

int minSweets(int current, const vector<int> &studentCount, int totalFaculties) {
    if (current == totalFaculties - 1) {
        return 0;
    }

    int min_cost = 0;

    int costToNext = 0;
    if (current + 1 < totalFaculties) {
        costToNext = abs(studentCount[current] - studentCount[current + 1]) + minSweets(current + 1, studentCount, totalFaculties);
        min_cost = costToNext;
    }

    int costToNextTwo = 0;
    if (current + 2 < totalFaculties) {
        costToNextTwo = abs(studentCount[current] - studentCount[current + 2]) + minSweets(current + 2, studentCount, studentCount.size());
        if (min_cost == 0 || costToNextTwo < min_cost) {
            min_cost = costToNextTwo;
        }
    }

    return min_cost;
}

int main() {
    int totalFaculties;
    cin >> totalFaculties;

    vector<int> studentCount(totalFaculties);
    for (int i = 0; i < totalFaculties; ++i) {
        cin >> studentCount[i];
    }

    int result = minSweets(0, studentCount, totalFaculties);
    cout << result << endl;
    return 0;
}
