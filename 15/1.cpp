#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll gpssum (vector<string>& map) {
    ll sum = 0;
    for (int i = 0; i < map.size(); ++i) {
        for (int j = 0; j < map[i].size(); ++j) {
            if (map[i][j] == 'O') {
                sum += (100 * i) + j;
            }
        }
    }
    
    return sum;
}

void simulate (vector<string>& map, pair<int,int>& rpos, char m) {
    
    vector<pair<int, int>> directions = {
        {-1, 0}, // Up
        {0, 1},  // Right
        {1, 0},  // Down
        {0, -1}  // Left
    };

    /* Printing map for debugging
    for (int i = 0; i < map.size(); ++i) {
        for (int j = 0; j < map[i].size(); ++j) {
            cout << map[i][j];
        }
        cout << endl;
    }
    */

    int dir_index = 0;
    if (m == '^') dir_index = 0;
    else if (m == '>') dir_index = 1;
    else if (m == 'v') dir_index = 2;
    else if (m == '<') dir_index = 3;

    int dx = directions[dir_index].first;
    int dy = directions[dir_index].second;

    int new_x = rpos.first + dx;
    int new_y = rpos.second + dy;

    char target = map[new_x][new_y];
    if (target == '#') {
        return;
    } else if (target == '.') {
        swap(map[rpos.first][rpos.second], map[new_x][new_y]);
        rpos = {new_x, new_y};
    } else if (target == 'O') {
        int chain_x = new_x;
        int chain_y = new_y;
        vector<pair<int, int>> block_positions;

        // Collect all positions of consecutive 'O's in the direction
        while (map[chain_x][chain_y] == 'O') {
            block_positions.push_back({chain_x, chain_y});
            chain_x += dx;
            chain_y += dy;
        }

        if (map[chain_x][chain_y] != '.') return;

        // Move the entire chain of blocks
        for (int i = block_positions.size() - 1; i >= 0; --i) {
            int bx = block_positions[i].first;
            int by = block_positions[i].second;
            map[bx + dx][by + dy] = 'O';
            map[bx][by] = '.'; 
        }

        // Move the robot
        map[new_x][new_y] = '@';
        map[rpos.first][rpos.second] = '.';
        rpos = {new_x, new_y};
    }
}


int main() {
    ifstream fin("input_map.in");
    ifstream sfin("input_moves.in");

    vector<string> map;
    string line;
    while (getline(fin, line)) {
        map.push_back(line);
    }

    // Find robot pos
    int x = -1, y = -1;
    for (int i = 0; i < map.size(); ++i) {
        for (int j = 0; j < map[i].size(); ++j) {
            if (map[i][j] == '@') {
                x = i;
                y = j;
                break;
            }
        }
    }

    pair<int, int> rpos = {x, y};

    char m;
    while (sfin >> m) {
        simulate(map, rpos, m);        
    }

    /* Print map for debugging
    for (int i = 0; i < map.size(); ++i) {
        for (int j = 0; j < map[i].size(); ++j) {
            cout << map[i][j];
        }
        cout << endl;
    }
    */

    cout << gpssum(map) << endl;
}

