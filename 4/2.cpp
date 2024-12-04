#include <bits/stdc++.h>
using namespace std;

int main() {
    ifstream fin("input.in");

    vector<string> grid;
    string line;
    while (getline(fin, line)) {
        grid.push_back(line);
    }

    int rows = grid.size();
    int cols = grid[0].size();
    int total = 0;

    // Check if a given 3x3 window matches the X-MAS pattern
    // OMG! Lambdas in C++, passes in grid by reference [&] from surrounding scope!
    // Doesn't even matter if another array as can infer the name!
    // Thank you ChatGPT for telling me that this exists, 
    // No thanks for being unable to implement a solution though :(
    auto matches_xmas = [&](int r, int c) {
        char top_left = grid[r][c]; 
        char top_right = grid[r][c + 2];
        char mid = grid[r + 1][c + 1];
        char bottom_left = grid[r + 2][c];
        char bottom_right = grid[r + 2][c + 2];

        bool centre_valid = (mid == 'A');
        bool left_valid = (top_left == 'M' && bottom_right == 'S') || (top_left == 'S' && bottom_right == 'M');
        bool right_valid = (top_right == 'M' && bottom_left == 'S') || (top_right == 'S' && bottom_left == 'M');

        return left_valid && right_valid && centre_valid;
    };

    // Slide a 3x3 window over the grid
    for (int r = 0; r <= rows - 3; ++r) {
        for (int c = 0; c <= cols - 3; ++c) {
            if (matches_xmas(r, c)) {
                total++;
            }
        }
    }

    cout << total << endl;

    return 0;
}
