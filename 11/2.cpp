#include <bits/stdc++.h>

typedef long long ll;
using namespace std;

struct pair_hash {
    template <class T1, class T2>
    size_t operator()(const pair<T1, T2>& p) const {
        auto h1 = hash<T1>{}(p.first);
        auto h2 = hash<T2>{}(p.second);
        return h1 ^ (h2 << 1);
    }
};

// <stones, blinks> is key, result is value
// Just need a custom pair hashing func as c++ doesn't give one
unordered_map<pair<ll, int>, ll, pair_hash> memo;

pair<ll, ll> split_number(ll stone) {
    int len = log10(stone) + 1; 
    int half_len = len / 2;
    ll divisor = pow(10, half_len); 
    ll left = stone / divisor;
    ll right = stone % divisor;
    return {left, right};
}

ll simulate(ll stone, int blinks) {
    if (blinks == 0) return 1; 

    // Check if result is cached
    pair<ll, int> state = {stone, blinks};
    if (memo.count(state)) return memo[state];

    ll result = 0;

    if (stone == 0) {
        result = simulate(1, blinks - 1);
    } else {
        int len = log10(stone) + 1;
        if (len % 2 == 0) {
            auto [left, right] = split_number(stone);
            result = simulate(left, blinks - 1) + simulate(right, blinks - 1);
        } else {
            result = simulate(stone * 2024, blinks - 1);
        }
    }

    memo[state] = result;
    return result;
}

ll count_stones(ll initial_stone, int blinks) {
    return simulate(initial_stone, blinks);
}

int main() {
    ifstream fin("input.in");
    ll totalCount = 0;
    ll stone;
    
    while (fin >> stone) {
        totalCount += count_stones(stone, 75);
    }
    
    cout << totalCount << endl;
    return 0;
}
