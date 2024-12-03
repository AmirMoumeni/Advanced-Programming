#include <iostream>
#include <vector>
#include <set>
#include <string>

using namespace std;

int compute(int left, int right, char op) {
    if (op == '+') return left + right;
    else if (op == '-') return left - right;
    else if (op == '*') return left * right;
    return 0;
}
vector<int> diffWaysToCompute(const string &expression) {
    vector<int> results;

    for (int i = 0; i < expression.size(); i++) {
        if (expression[i] == '+' || expression[i] == '-' || expression[i] == '*') {
            vector<int> leftResults = diffWaysToCompute(expression.substr(0, i));
            vector<int> rightResults = diffWaysToCompute(expression.substr(i + 1));

            for (int left : leftResults) {
                for (int right : rightResults) {
                    results.push_back(compute(left, right, expression[i]));
                }
            }
        }
    }

    if (results.empty()) {
        results.push_back(stoi(expression));
    }

    return results;
}

int main() {
    int n;
    string expression;

    cin >> n;
    cin >> expression;

    vector<int> results = diffWaysToCompute(expression);
    set<int> uniqueResults(results.begin(), results.end());

    cout << uniqueResults.size() << endl;
    return 0;
}
