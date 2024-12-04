#include <bits/stdc++.h>
using namespace std;
typedef long long ll;


int main() {
    ifstream fin("input.in");

    // input is 140 x 140
    vector<string> grid;
    string line;
    while (getline(fin, line)) {
        grid.push_back(line);
    }

    int rows = grid.size();
    int cols = grid[0].size();
    string word = "XMAS";
    int total = 0;

    // Direction vectors for 8 directions
    // Grid [row][column], annoyingly opposite to cartesian so hard to think about
    vector<pair<int, int>> directions = {
        {0, 1},  // Right
        {0, -1}, // Left
        {1, 0},  // Down
        {-1, 0}, // Up
        {1, 1},  // Diagonal down-right
        {1, -1}, // Diagonal down-left
        {-1, 1}, // Diagonal up-right
        {-1, -1} // Diagonal up-left
    };

    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            if (grid[r][c] == 'X') {
                for (auto [dr, dc] : directions) { //i.e direction in directions
                    int x = r, y = c;
                    bool match = true;

                    // Check characters in the word "XMAS"
                    // And handle the many many edge cases for out of bounds errors ...
                    for (int k = 0; k < word.size(); ++k) {
                        if (x < 0 || x >= rows || y < 0 || y >= cols || grid[x][y] != word[k]) {
                            match = false;
                            break;
                        }

                        // Move to next cell in direction
                        x += dr;
                        y += dc;
                    }

                    if (match) {
                        total++;
                    }
                }
            }
        }
    }

    cout << total << endl;

}