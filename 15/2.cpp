#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll gpssum (vector<string>& map) {
    ll sum = 0;
    for (int i = 0; i < map.size(); ++i) {
        for (int j = 0; j < map[i].size(); ++j) {
            if (map[i][j] == '[') {
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

    // Printing map for debugging
    for (int i = 0; i < map.size(); ++i) {
        for (int j = 0; j < map[i].size(); ++j) {
            cout << map[i][j];
        }
        cout << endl;
    }
    

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
    } else if (target == '[' || target == ']') {
        int chain_x = new_x;
        int chain_y = new_y;

        vector<pair<int, int>> block_positions;

        // Check if the current position is part of a chain
        bool lside = map[chain_x][chain_y] == '[';
        bool rside = map[chain_x][chain_y] == ']';

        // Collect the entire chain of block positions
        // Aligned to left bracket for each block []
        while (lside || rside) {
            if (lside) {
                block_positions.push_back({chain_x, chain_y});
                chain_x += dx;
                chain_y += dy; // Should change depending on up/down/left right
            } else {
                block_positions.push_back({chain_x, chain_y - 1});
                chain_x += dx;
                chain_y += dy - 1; // Should change depending on up/down/left right
            }

            lside = map[chain_x][chain_y] == '[';
            rside = map[chain_x][chain_y] == ']';
        }

        for (auto block : block_positions) {
            // if either the block in front or the block in front or the block infront and right (as [ aligned)
            // is a #, then return; because the chain cannot move (This is for moving vertically up/down)
            // if left right, only need to check block at the end of chain is a .
        }


        // Now that checks confirm it is safe to move stack, move it
        // left/right/up down

        // Update the robot
        map[new_x][new_y] = '@';
        map[rpos.first][rpos.second] = '.';
        rpos = {new_x, new_y};
    }
}

int main() {
    ifstream fin("test_map.in");
    ifstream sfin("test_moves.in");

    vector<string> map;
    string line;
    while (getline(fin, line)) {
        string new_line;
        for (char c : line) {
            if (c == '#') new_line += "##";
            else if (c == 'O') new_line += "[]";
            else if (c == '.') new_line += "..";
            else if (c == '@') new_line += "@.";
        }
        map.push_back(new_line);
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

    // Print map for debugging
    for (int i = 0; i < map.size(); ++i) {
        for (int j = 0; j < map[i].size(); ++j) {
            cout << map[i][j];
        }
        cout << endl;
    }
    
    cout << gpssum(map) << endl;
}
