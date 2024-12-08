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

                vector<pii> potential_antinodes = {
                    {x1 - dx, y1 - dy},
                    {x2 + dx, y2 + dy}
                };

                for (const auto& [ax, ay] : potential_antinodes) {
                    if (in_bounds(ax, ay, height, width)) {
                        unique_antinodes.insert({ax, ay});
                    }
                }
            }
        }
    }

    cout << unique_antinodes.size() << endl;

    return 0;
}
