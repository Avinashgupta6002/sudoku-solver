#include <iostream>
#include <vector>

using namespace std;

const int N = 9; // Size of the Sudoku grid

// Function to print the Sudoku grid
void printGrid(const vector<vector<int>>& grid) {
    for (const auto& row : grid) {
        for (int num : row) {
            cout << num << " ";
        }
        cout << endl;
    }
}

// Function to check if a number can be placed in a given position
bool isSafe(const vector<vector<int>>& grid, int row, int col, int num) {
    // Check the row and column
    for (int x = 0; x < N; x++) {
        if (grid[row][x] == num || grid[x][col] == num) {
            return false;
        }
    }

    // Check the 3x3 box
    int startRow = row - row % 3, startCol = col - col % 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (grid[i + startRow][j + startCol] == num) {
                return false;
            }
        }
    }

    return true;
}

// Backtracking function to solve the Sudoku
bool solveSudoku(vector<vector<int>>& grid) {
    int row, col;
    bool empty = true;

    // Find an empty space in the grid
    for (row = 0; row < N; row++) {
        for (col = 0; col < N; col++) {
            if (grid[row][col] == 0) { // 0 indicates an empty cell
                empty = false;
                break;
            }
        }
        if (!empty) break;
    }

    // If no empty space is found, the puzzle is solved
    if (empty) return true;

    // Try numbers from 1 to 9
    for (int num = 1; num <= N; num++) {
        if (isSafe(grid, row, col, num)) {
            grid[row][col] = num; // Place the number

            // Recursively try to solve the rest of the grid
            if (solveSudoku(grid)) return true;

            // If it doesn't lead to a solution, reset and try another number
            grid[row][col] = 0;
        }
    }

    return false; // Trigger backtracking
}

int main() {
    // Example Sudoku puzzle (0s represent empty cells)
    vector<vector<int>> grid = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };

    cout << "Sudoku Puzzle:\n";
    printGrid(grid);

    if (solveSudoku(grid)) {
        cout << "\nSolved Sudoku:\n";
        printGrid(grid);
    } else {
        cout << "No solution exists.";
    }

    return 0;
}