#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

bool canMoveBlocks(int dx, int dy, ll cx, ll cy, vector<string>& map) {
    if (map[cy][cx] == '#') {
        return false;
    } else if (map[cy][cx] == '.') {
        return true;
    } else {
        if (dy != 0) { // The vertical case
            if (map[cy][cx] == '[') {
                return canMoveBlocks(dx, dy, cx, cy + dy, map) && canMoveBlocks(dx, dy, cx + 1, cy + dy, map);
            } else {
                return canMoveBlocks(dx, dy, cx, cy + dy, map) && canMoveBlocks(dx, dy, cx - 1, cy + dy, map);
            }
        } else {
            return canMoveBlocks(dx, dy, cx + dx, cy + dy, map);
        }
    }
}

void moveBlocks(int dx, int dy, ll cx, ll cy, vector<string>& map) {
    if (map[cy][cx] == '.') {
        return;
    }
    if (dy != 0) { // The vertical case for the next one
        if (map[cy][cx] == '[') {
            moveBlocks(dx, dy, cx + 1, cy + dy, map);
            map[cy + dy][cx + 1] = map[cy][cx + 1];
            map[cy][cx + 1] = '.';
        } else {
            moveBlocks(dx, dy, cx - 1, cy + dy, map);
            map[cy + dy][cx - 1] = map[cy][cx - 1];
            map[cy][cx - 1] = '.';
        }
    }
    moveBlocks(dx, dy, cx + dx, cy + dy, map);
    map[cy + dy][cx + dx] = map[cy][cx];
    map[cy][cx] = '.';
}

ll gpssum(vector<string>& map) {
    ll sum = 0;
    for (ll y = 0; y < map.size(); ++y) {
        for (ll x = 0; x < map[0].size(); ++x) {
            if (map[y][x] == '[') {
                sum += 100 * y + x;
            }
        }
    }
    return sum;
}

int main() {
    ifstream inputFile("input.in");
    vector<pair<int, int>> moves;
    string line;
    vector<string> map;
    ll cx, cy;
    bool isMap = true;
    int y = 0;
    
    while (getline(inputFile, line)) {
        if (line.empty()) {
            isMap = false;
        } else if (isMap) {
            string temp = "";
            for (int x = 0; x < line.size(); ++x) {
                if (line[x] == '@') {
                    cx = 2 * x; // We multiply by 2 to adjust for doubled-width map
                    cy = y;
                    temp += "@.";
                } else if (line[x] == 'O') {
                    temp += "[]";
                } else if (line[x] == '.') {
                    temp += "..";
                } else {
                    temp += "##";
                }
            }
            map.push_back(temp);
        } else {
            for (char m : line) {
                switch (m) {
                    case '<': moves.push_back({-1, 0}); break;
                    case '^': moves.push_back({0, -1}); break;
                    case '>': moves.push_back({1, 0}); break;
                    case 'v': moves.push_back({0, 1}); break;
                    default: break;
                }
            }
        }
        ++y;
    }

    pair<int, int> rpos = {cx, cy};

    for (auto [dx, dy] : moves) {
        if (canMoveBlocks(dx, dy, rpos.first + dx, rpos.second + dy, map)) {
            moveBlocks(dx, dy, rpos.first + dx, rpos.second + dy, map);
            map[rpos.second][rpos.first] = '.';
            map[rpos.second + dy][rpos.first + dx] = '@';
            rpos.first += dx;
            rpos.second += dy;
        }
    }

    ll s = gpssum(map);

    // Print the map
    // for (const auto& row : map) {
    //     cout << row << endl;
    // }

    cout << s << endl;
    return 0;
}
