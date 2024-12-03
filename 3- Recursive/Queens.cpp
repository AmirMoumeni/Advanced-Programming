#include <iostream>
#include <vector>
using namespace std;

const int N = 8;

bool isSafe(const vector<string> &board, vector<int> &rows, int row, int col) {
    if (board[row][col] == '*') return false;
    for (int i = 0; i < row; i++) {
        if (rows[i] == col || abs(rows[i] - col) == abs(i - row)) {
            return false;
        }
    }
    return true;
}

void solveNQueens(const vector<string> &board, vector<int> &rows, int row, int &solutions) {
    if (row == N) {
        solutions++;
        return;
    }
    
    for (int col = 0; col < N; col++) {
        if (isSafe(board, rows, row, col)) {
            rows[row] = col;
            solveNQueens(board, rows, row + 1, solutions);
            rows[row] = -1;
        }
    }
}

int main() {
    vector<string> board(N);
    for (int i = 0; i < N; i++) {
        getline(cin ,board[i]);
    }

    vector<int> rows(N, -1);
    int solutions = 0;
    solveNQueens(board, rows, 0, solutions);

    cout << solutions << endl;
    return 0;
}
