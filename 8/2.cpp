#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

bool in_bounds(int x, int y, int height, int width) {
    return x >= 0 && x < width && y >= 0 && y < height;
}

int main() {
    ifstream fin("input.in");
    vector<string> map;
    string line;

    while (getline(fin, line)) {
        map.push_back(line);
    }

    int height = map.size();
    int width = map[0].size();


    // Thanks @KOLESNiii for telling me about hash maps
    unordered_map<char, vector<pii>> antenna_positions;

    // Positions of each antenna
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            char c = map[y][x];
            if (isalnum(c)) { 
                antenna_positions[c].emplace_back(x, y);
            }
        }
    }

    // Antinodes for each antenna type
    set<pii> unique_antinodes;
    for (const auto& [type, positions] : antenna_positions) {
        int n = positions.size();
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                int x1 = positions[i].first, y1 = positions[i].second;
                int x2 = positions[j].first, y2 = positions[j].second;

                int dx = x2 - x1;
                int dy = y2 - y1;

                int ax = x1, ay = y1;
                while (in_bounds(ax, ay, height, width)) {
                    unique_antinodes.insert({ax, ay});
                    ax -= dx;
                    ay -= dy;
                }

                ax = x2;
                ay = y2;
                while (in_bounds(ax, ay, height, width)) {
                    unique_antinodes.insert({ax, ay});
                    ax += dx;
                    ay += dy;
                }

            }
        }
    }

    cout << unique_antinodes.size() << endl;

    return 0;
}
