#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

ll solve (ll Ax, ll Ay, ll Bx, ll By, ll Px, ll Py) {
    ll det = Ax*By - Bx*Ay;

    if (det == 0) {
        cerr << "Matrix is singular, no inverse exists." << endl;
        return -1;
    }

    ll a = (Px * By - Py * Bx);
    ll b = (Ax * Py - Ay * Px);

    if (a % det != 0 || b % det != 0) {
        return 0; // No integer solution
    }

    a /= det;
    b /= det;

    if (a < 0 || b < 0) {
        return 0;
    }

    return 3 * a + b;
}

int main() {
    ifstream fin("input.in");

    ll total_tokens = 0;

    string line;
    while (getline(fin, line)) {
        if (line.empty()) continue;
        
        ll Ax = 0, Ay = 0, Bx = 0, By = 0, Px = 0, Py = 0;

        if (line.find("Button A:") != string::npos) {
            if (sscanf(line.c_str(), "Button A: X+%lld, Y+%lld", &Ax, &Ay) != 2) {
                cerr << "Failed to parse Button A: " << line << endl;
                continue;
            }
        } else {
            cerr << "Expected Button A line, but got: " << line << endl;
            continue;
        }

        if (!getline(fin, line) || sscanf(line.c_str(), "Button B: X+%lld, Y+%lld", &Bx, &By) != 2) {
            cerr << "Failed to parse Button B: " << line << endl;
            continue;
        }

        if (!getline(fin, line) || sscanf(line.c_str(), "Prize: X=%lld, Y=%lld", &Px, &Py) != 2) {
            cerr << "Failed to parse Prize: " << line << endl;
            continue;
        }

        Px += 10000000000000;
        Py += 10000000000000;

        total_tokens += solve(Ax, Ay, Bx, By, Px, Py);
    }

    cout << total_tokens << endl;
}
