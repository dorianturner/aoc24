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

    vector<pair<int,int>> theads;
    int x = -1, y = -1;
    for (int i = 0; i < map.size(); ++i) {
        for (int j = 0; j < map[i].size(); ++j) {
            if (map[i][j] == 0) {
                x = i;
                y = j;
                theads.push_back({x, y});
            }
        }
    }

    // BFS function to count how many 9's can be reached from a start position
    auto bfs = [&](int start_x, int start_y) {
        int n = map.size();
        int m = map[0].size();
        queue<pair<int, int>> q;
        vector<vector<bool>> visited(n, vector<bool>(m, false));
        
        q.push({start_x, start_y});
        visited[start_x][start_y] = true;
        
        int count_nines = 0;

        while (!q.empty()) {
            auto [x, y] = q.front();
            q.pop();
            
            if (map[x][y] == 9) count_nines++;

            for (auto [dx, dy] : directions) {
                int nx = x + dx;
                int ny = y + dy;
                
                if (nx >= 0 && nx < n && ny >= 0 && ny < m) {
                    if (!visited[nx][ny]) {
                        if (map[nx][ny] == map[x][y] + 1) {
                            visited[nx][ny] = true;
                            q.push({nx, ny});
                        }
                    }
                }
            }
        }

        return count_nines;
    };

    int total_nines = 0;

    for (auto [start_x, start_y] : theads) {
        total_nines += bfs(start_x, start_y);
    }

    cout << total_nines << endl;

    return 0;
}
