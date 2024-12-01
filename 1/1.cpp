#include <bits/stdc++.h>

using namespace std;

int main() {

    ifstream fin("input.in");
    ofstream fout("output.out");

    vector<int> left, right;
    int l, r;

    while (fin >> l >> r) {
        left.push_back(l);
        right.push_back(r);
    }

    sort(left.begin(),left.end());
    sort(right.begin(),right.end());

    int sum = 0;
    for (int i = 0; i < left.size(); i++) {
        sum += abs(left[i] - right[i]);
    }

    fout << sum;
}