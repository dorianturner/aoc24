#include <bits/stdc++.h>
#include <map>
#include <set>
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

// BFS function to find the minimum costs and paths to each position
map<pair<int, int>, ll> bfs(vector<string>& map, int sx, int sy) {
    int height = map.size();
    int width = map[0].size();
    
    priority_queue<State, vector<State>, greater<State>> pq;
    
    // Visited array to track the minimum cost to reach a position in a specific direction
    vector<vector<vector<ll>>> visited(height, vector<vector<ll>>(width, vector<ll>(4, LLONG_MAX)));
    
    // Cost to get to each (x, y) position with the minimum cost from 'S'
    map<pair<int, int>, ll> min_cost_to_position;
        
    pq.push({sx, sy, 0, 0});
    visited[sy][sx][0] = 0;
    min_cost_to_position[{sx, sy}] = 0;
    
    while (!pq.empty()) {
        State current = pq.top();
        pq.pop();
        
        int x = current.x;
        int y = current.y;
        int dir = current.direction;
        ll cost = current.cost;
        
        if (cost > visited[y][x][dir]) {
            continue;
        }
        
        min_cost_to_position[{x, y}] = min(min_cost_to_position[{x, y}], cost);

        // Move forward
        int nx = x + dx[dir];
        int ny = y + dy[dir];
        if (ny >= 0 && ny < height && nx >= 0 && nx < width && map[ny][nx] != '#') { 
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
    
    return min_cost_to_position;
}

void trace_min_paths(vector<string>& map, map<pair<int, int>, ll>& min_cost_to_position, set<pair<int, int>>& seats) {
    int height = map.size();
    int width = map[0].size();
    
    for (auto& [pos, min_cost] : min_cost_to_position) {
        int x = pos.first;
        int y = pos.second;
        
        for (int dir = 0; dir < 4; ++dir) {
            int nx = x + dx[dir];
            int ny = y + dy[dir];
            if (ny >= 0 && ny < height && nx >= 0 && nx < width && map[ny][nx] != '#') {
                ll step_back_cost = min_cost - 1;
                if (min_cost_to_position.count({nx, ny}) && min_cost_to_position[{nx, ny}] == step_back_cost) {
                    seats.insert({x, y});
                }
            }
        }
    }
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

    // Find start position 'S'
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            if (map[i][j] == 'S') {
                sx = j;
                sy = i;
                break;
            }
        }
    }
    
    set<pair<int, int>> seats;
    
    map<pair<int, int>, ll> min_cost_to_position = bfs(map, sx, sy);
    
    trace_min_paths(map, min_cost_to_position, seats);

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            if (seats.count({j, i})) {
                cout << 'O';
            } else {
                cout << map[i][j];
            }
        }
        cout << endl;
    }
    
    cout << seats.size() << endl;
}
