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

// Cheers to Tim / Leo for telling me to use dfs cos I had no idea how to scope out the regions
void dfs(int x, int y, vector<string>& map, vector<vector<bool>>& visited, char plant_type, int& area, int& perimeter) {
    stack<pair<int, int>> s;
    s.push({x, y});
    visited[x][y] = true;

    while (!s.empty()) {
        auto [cx, cy] = s.top();
        s.pop();
        area++;

        for (auto [dx, dy] : directions) {
            int nx = cx + dx;
            int ny = cy + dy;
            if (is_valid(nx, ny)) {
                if (map[nx][ny] == plant_type) {
                    if (!visited[nx][ny]) {
                        s.push({nx, ny});
                        visited[nx][ny] = true;
                    }
                } else {
                    perimeter++;
                }
            } else {
                // External edge
                perimeter++;
            }
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

    n = map.size();
    m = map[0].size();
    
    vector<vector<bool>> visited(n, vector<bool>(m, false)); 
    ll total_cost = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (!visited[i][j]) {
                int area = 0, perimeter = 0;
                char plant_type = map[i][j];
                
                // Calculate area and perimeter of this region
                dfs(i, j, map, visited, plant_type, area, perimeter);
                
                // Calculate cost for this region
                ll region_cost = area * perimeter;
                total_cost += region_cost;
            }
        }
    }

    cout << total_cost << endl;
    
    return 0;
}