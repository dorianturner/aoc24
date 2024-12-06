#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

bool loops(vector<string> map) {
    vector<pair<int, int>> directions = {
        {-1, 0}, // Up
        {0, 1},  // Right
        {1, 0},  // Down
        {0, -1}  // Left
    };

    vector<vector<int>> dirs(map.size(), vector<int>(map[0].size(), -1));

    // Find guard position
    int x = -1, y = -1;
    for (int i = 0; i < map.size(); ++i) {
        for (int j = 0; j < map[i].size(); ++j) {
            if (map[i][j] == '^') {
                x = i;
                y = j;
                break;
            }
        }
    }

    int dir = 0;

    while (true) {
        // Check the tile in front of the guard
        int nx = x + directions[dir].first;
        int ny = y + directions[dir].second;

        bool ny_invalid = ny < 0 || ny >= map[0].size();
        bool nx_invalid = nx < 0 || nx >= map.size();
        if (nx_invalid || ny_invalid) {
            return false;
        }

        // If the guard is visiting the same position and direction, looped
        if (dirs[nx][ny] != -1 && dirs[nx][ny] == dir) {
            return true;
        }

        if (map[nx][ny] == '#') {
            dir = (dir + 1) % 4;  // Cycle to next direction
        } else {
            x = nx;
            y = ny;

            dirs[x][y] = dir;
        }
    }
}

int main() {
    ifstream fin("input.in");

    vector<string> map;
    string line;
    while (getline(fin, line)) {
        map.push_back(line);
    }

    int count = 0;

    for (int i = 0; i < map.size(); ++i) {
        for (int j = 0; j < map[0].size(); ++j) {
            auto modified_map = map;
            modified_map[i][j] = '#';

            if (loops(modified_map)) {
                count++;
            }
        }
    }

    cout << count << endl;
}
