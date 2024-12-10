#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ifstream fin("input.in");
    vector<vector<int>> map;
    string line;

    while (getline(fin, line)) {
        vector<int> row;
        for (char c : line) {
            row.push_back(c - '0');
        }
        map.push_back(row);
    }

    vector<pair<int, int>> directions = {
        {-1, 0}, // Up
        {0, 1},  // Right
        {1, 0},  // Down
        {0, -1}  // Left
    };

    vector<pair<int, int>> trailheads;
    for (int i = 0; i < map.size(); ++i) {
        for (int j = 0; j < map[i].size(); ++j) {
            if (map[i][j] == 0) {
                trailheads.push_back({i, j});
            }
        }
    }

    int n = map.size();
    int m = map[0].size();
    
    // Total paths to all 9s
    int total_paths_to_nines = 0;

    // BFS function to count paths to each position for a specific trailhead
    auto bfs = [&](int start_x, int start_y) {
        queue<pair<int, int>> q;
        vector<vector<int>> local_path_count(n, vector<int>(m, 0));

        q.push({start_x, start_y});
        local_path_count[start_x][start_y] = 1; 
        
        while (!q.empty()) {
            auto [x, y] = q.front();
            q.pop();
            
            for (auto [dx, dy] : directions) {
                int nx = x + dx;
                int ny = y + dy;
                
                if (nx >= 0 && nx < n && ny >= 0 && ny < m) {
                    if (map[nx][ny] == map[x][y] + 1) {
                        if (local_path_count[nx][ny] == 0) {
                            q.push({nx, ny});
                        }
                        local_path_count[nx][ny] += local_path_count[x][y];
                    }
                }
            }
        }

        int paths_to_nines = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (map[i][j] == 9) {
                    paths_to_nines += local_path_count[i][j];
                }
            }
        }
        
        return paths_to_nines;
    };

    for (auto [start_x, start_y] : trailheads) {
        total_paths_to_nines += bfs(start_x, start_y);
    }

    cout << total_paths_to_nines << endl;

    return 0;
}
