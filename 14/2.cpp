#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

// Holy **** this p2 was so bad, I checked the unique times sequentially in order
// Why can they not give us an example of a christmas tree !?!?
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

    for (int t = 0; ; ++t) {
        bool overlapping_bot = false;
        set<pair<int, int>> unique_positions;

        for (auto& robot : robots) {
            int x = robot.first.first;
            int y = robot.first.second;

            if (!unique_positions.insert({x, y}).second) {
                overlapping_bot = true;
            }
        }

        if (!overlapping_bot) {
            cout << t << endl;
        }

        for (auto& robot : robots) {
            ll& x = robot.first.first;
            ll& y = robot.first.second;
            ll vx = robot.second.first;
            ll vy = robot.second.second;
            
            x = (x + vx + width) % width; // wrap horizontally
            y = (y + vy + height) % height; // wrap vertically
        }
    }
}