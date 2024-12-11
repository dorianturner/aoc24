#include <bits/stdc++.h>

typedef long long ll;
using namespace std;

// Was having a headache figuring out how to do two recursive calls
// And update acc appropriately with tail recursion
// Then I just realised I could make acc a global variable
// And simulate could just update that rather than return anything :)
void simulate(ll stone, int blinks, ll &acc) {
    string s = to_string(stone);
    int len = s.length();

    if (blinks == 0) {
        acc += 1;
        return;
    }

    if (stone == 0) {
        simulate(1, blinks - 1, acc);
    } else if (len % 2 == 0) {
        ll left = stoll(s.substr(0, len / 2));
        ll right = stoll(s.substr(len / 2));
        simulate(left, blinks - 1, acc);
        simulate(right, blinks - 1, acc);
    } else {
        simulate(stone * 2024, blinks - 1, acc);
    }
}

ll count_stones(ll initial_stone, int blinks) {
    ll acc = 0;
    simulate(initial_stone, blinks, acc);
    return acc;
}

int main() {
    ifstream fin("input.in");
    ll totalCount = 0;
    ll stone;
    
    while (fin >> stone) {
        totalCount += count_stones(stone, 25);
    }
    
    cout << totalCount << endl;
    return 0;
}