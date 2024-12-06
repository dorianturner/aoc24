#include <bits/stdc++.h>
using namespace std;
typedef long long ll;


int main() {
    ifstream fin("input.in");

    vector<string> map;
    string line;
    while (getline(fin, line)) {
        map.push_back(line);
    }

    vector<pair<int, int>> directions = {
        {-1, 0}, // Up
        {0, 1},  // Right
        {1, 0},  // Down
        {0, -1}  // Left
    };

    // Find guard pos
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
    int count = 0;

    while (true) {
        // Check the tile in front of the guard
        int dx = directions[dir].first;
        int dy = directions[dir].second;

        // Check if the guard has moved off the edge of the map
        bool ny_invalid = y + dy < 0 || y + dy >= map[0].size();
        bool nx_invalid = x + dx < 0 || x + dx >= map.size();
        if (nx_invalid || ny_invalid ) {
            break;
        }

        if (map[x + dx][y + dy] == '#') {
            dir = (dir + 1) % 4;  // Cycle to next direction 
        } else {
            x += dx;
            y += dy;

            if (map[x][y] != 'X') {  
                map[x][y] = 'X';
                count++;
            }
        }
    }

    cout << count << endl;

}