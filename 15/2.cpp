#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll gpssum(vector<string>& map) {
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

bool canMoveBlocks(int dx, int dy, int x, int y, vector<string>& map) {
    if (map[y][x] == '#') {
        return false;
    } else if (map[y][x] == '.') {
        return true;
    } else {
        if (dy != 0) {
            if (map[y][x] == '[') {
                return canMoveBlocks(dx, dy, x, y + dy, map) && canMoveBlocks(dx, dy, x + 1, y + dy, map);
            } else {
                return canMoveBlocks(dx, dy, x, y + dy, map) && canMoveBlocks(dx, dy, x - 1, y + dy, map);
            }
        } else {
            return canMoveBlocks(dx, dy, x + dx, y + dy, map);
        }
    }
}

void moveBlocks(int dx, int dy, int x, int y, vector<string>& map) {
    if (map[y][x] == '.') {
        return;
    }
    if (dy != 0) {
        if (map[y][x] == '[') {
            moveBlocks(dx, dy, x + 1, y + dy, map);
            map[y + dy][x + 1] = map[y][x + 1];
            map[y][x + 1] = '.';
        } else {
            moveBlocks(dx, dy, x - 1, y + dy, map);
            map[y + dy][x - 1] = map[y][x - 1];
            map[y][x - 1] = '.';
        }
    }
    moveBlocks(dx, dy, x + dx, y + dy, map);
    map[y + dy][x + dx] = map[y][x];
    map[y][x] = '.';
}

void simulate(vector<string>& map, pair<int, int>& rpos, char m) {
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

    char target = map[new_y][new_x];

    if (target == '#') {
        return;
    } else if (target == '.') {
        swap(map[rpos.second][rpos.first], map[new_y][new_x]);
        rpos = {new_x, new_y};
    } else if (canMoveBlocks(dx, dy, new_x, new_y, map)) {
        moveBlocks(dx, dy, new_x, new_y, map);
        swap(map[rpos.second][rpos.first], map[new_y][new_x]);
        rpos = {new_x, new_y};
    }

    return;
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
