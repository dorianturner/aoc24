#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct State {
    int x, y, direction;
    ll cost;

    // For priority queue to prioritize lower cost paths
    bool operator>(const State& other) const {
        return cost > other.cost;
    }
};

// Directions: 0 = East, 1 = South, 2 = West, 3 = North
const int dx[4] = {1, 0, -1, 0};
const int dy[4] = {0, 1, 0, -1};

ll bfs(vector<string>& map, int sx, int sy) {
    int height = map.size();
    int width = map[0].size();
    
    // Priority queue for strange BFS, Leo recommended it
    priority_queue<State, vector<State>, greater<State>> pq;
    
    // Visited array to track the minimum cost to reach a position
    // Just use LLONG_MAX so don't have to think about when we first meet it cost calculations
    vector<vector<vector<ll>>> visited(height, vector<vector<ll>>(width, vector<ll>(4, LLONG_MAX)));
    
    pq.push({sx, sy, 0, 0});
    visited[sy][sx][0] = 0;LLONG_MAX
    
    while (!pq.empty()) {
        State current = pq.top();
        pq.pop();
        
        int x = current.x;
        int y = current.y;
        int dir = current.direction;
        ll cost = current.cost;
        
        if (map[y][x] == 'E') {
            return cost;
        }
        
        // If this state has been visited with a better cost, skip it
        if (cost > visited[y][x][dir]) {
            continue;
        }
        
        // Move forward
        int nx = x + dx[dir];
        int ny = y + dy[dir];
        if (map[ny][nx] != '#') {
            ll new_cost = cost + 1;
            if (new_cost < visited[ny][nx][dir]) {
                visited[ny][nx][dir] = new_cost;
                pq.push({nx, ny, dir, new_cost});
            }
        }
        
        // Turn left
        int new_dir = (dir + 3) % 4; 
        ll new_cost = cost + 1000;
        if (new_cost < visited[y][x][new_dir]) {
            visited[y][x][new_dir] = new_cost;
            pq.push({x, y, new_dir, new_cost});
        }
        
        // Turn right 
        new_dir = (dir + 1) % 4; 
        new_cost = cost + 1000;
        if (new_cost < visited[y][x][new_dir]) {
            visited[y][x][new_dir] = new_cost;
            pq.push({x, y, new_dir, new_cost});
        }
    }

    return -1;
}

int main() {
    ifstream inputFile("test.in");

    string line;
    vector<string> map;
    
    while (getline(inputFile, line)) {
        map.push_back(line);
    }

    int sx = -1, sy = -1;
    int height = map.size();
    int width = map[0].size();

    // Find Start
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            if (map[i][j] == 'S') {
                sx = j;
                sy = i;
                break;
            }
        }
    }
    
    ll result = bfs(map, sx, sy);
    
    cout << result << endl;
}
