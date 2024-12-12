#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

vector<pair<int, int>> directions = {
    {-1, 0}, // Up
    {0, 1},  // Right
    {1, 0},  // Down
    {0, -1}  // Left
};

int n, m;

bool is_valid(int x, int y) {
    return x >= 0 && x < n && y >= 0 && y < m;
}

void dfs(int x, int y, vector<string>& map, vector<vector<bool>>& visited, char plant_type, int& area, int& sides) {
    stack<pair<int, int>> s;
    s.push({x, y});
    visited[x][y] = true;

    while (!s.empty()) {
        auto [cx, cy] = s.top();
        s.pop();
        area++;
        vector<bool> dirs = {false, false, false, false}; // URDL

        for (int i = 0; i < 4; ++i) {
            int nx = cx + directions[i].first;
            int ny = cy + directions[i].second;
            if (is_valid(nx, ny)) {
                    if (map[nx][ny] == plant_type) {
                        if (!visited[nx][ny]) {
                            s.push({nx, ny});
                            visited[nx][ny] = true;
                        }
                    } else {
                        dirs[i] = true;
                    }
            } else {
                dirs[i] = true;
            }
        }

        // Outward facing corners
        for (int i = 0; i < 4; ++i) {
            int next = (i + 1) % 4;
            if (dirs[i] && dirs[next]) {
                sides++;
            }
        }

        // Inward facing corners
        vector<pair<int, int>> diagonals = {{-1, -1}, {-1, 1}, {1, 1}, {1, -1}};
        for (int i = 0; i < 4; ++i) {
            int dx = diagonals[i].first, dy = diagonals[i].second;
            int adj1_x = cx + dx, adj1_y = cy; 
            int adj2_x = cx, adj2_y = cy + dy; 
            int center_x = cx + dx, center_y = cy + dy; 

            if (is_valid(adj1_x, adj1_y) && is_valid(adj2_x, adj2_y) && is_valid(center_x, center_y)) {
                if (map[adj1_x][adj1_y] == plant_type && map[adj2_x][adj2_y] == plant_type && map[center_x][center_y] != plant_type) {
                    sides++;
                }
            }
        }

    }

    cout << map[x][y] << " Area: " << area << " Sides: " << sides << endl;
}

int main() {
    ifstream fin("input.in");

    vector<string> map;
    string line;
    while (getline(fin, line)) {
        map.push_back(line);
        // cout << line << endl;
    }
    
    n = map.size();
    m = map[0].size();
    
    vector<vector<bool>> visited(n, vector<bool>(m, false));
    ll total_cost = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (!visited[i][j]) { 
                int area = 0, sides = 0;
                char plant_type = map[i][j];
                
                // Calculate area and sides of this region
                dfs(i, j, map, visited, plant_type, area, sides);
                
                // Calculate cost for this region
                ll region_cost = area * sides;
                total_cost += region_cost;
            }
        }
    }

    cout << total_cost << endl;
    
    return 0;
}
