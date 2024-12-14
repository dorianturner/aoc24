#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int main() {
    ifstream fin("input.in");
    vector<pair<pair<ll, ll>, pair<ll, ll>>> robots; // ((px, py), (vx, vy))
    
    string line;
    while (getline(fin, line)) {
        if (line.empty()) continue;
        
        ll px, py, vx, vy;

        if (line.find("p=") != string::npos) {
            if (sscanf(line.c_str(), "p=%lld,%lld v=%lld,%lld", &px, &py, &vx, &vy) != 4) {
                cerr << "Failed to parse line: " << line << endl;
                continue;
            }
            
            robots.push_back({{px, py}, {vx, vy}});
        }
    }

    int width = 101, height = 103;
    int middle_x = width / 2, middle_y = height / 2;
    
    for (int t = 0; t < 100; ++t) {
        for (auto& robot : robots) {
            ll& x = robot.first.first;
            ll& y = robot.first.second;
            ll vx = robot.second.first;
            ll vy = robot.second.second;
            
            x = (x + vx + width) % width; // wrap horizontally
            y = (y + vy + height) % height; // wrap vertically
        }
    }
    
    vector<vector<int>> grid(height, vector<int>(width, 0));
    for (auto& robot : robots) {
        int x = robot.first.first;
        int y = robot.first.second;
        grid[y][x] += 1;
    }

    /* Print the grid in testing
    for (int y = 0; y < grid.size(); ++y) {
        for (int x = 0; x < grid[y].size(); ++x) {
            cout << grid[y][x];
        }
        cout << endl;
    }
    */
    
    int q1 = 0, q2 = 0, q3 = 0, q4 = 0;
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            if (y == middle_y || x == middle_x) continue;
            
            if (y < middle_y && x < middle_x) q1 += grid[y][x];
            else if (y < middle_y && x > middle_x) q2 += grid[y][x];
            else if (y > middle_y && x < middle_x) q3 += grid[y][x];
            else if (y > middle_y && x > middle_x) q4 += grid[y][x];
        }
    }
    
    ll safety_factor = q1 * q2 * q3 * q4;
    cout << safety_factor << endl;
    
    return 0;
}