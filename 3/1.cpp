#include <bits/stdc++.h>
using namespace std;

int main() {
    ifstream fin("input.in");

    string input, line;
    while (getline(fin, line)) {
        input += line;
    }

    regex valid_mul(R"(mul\((\d{1,3}),(\d{1,3})\))");
    smatch match;
    int total = 0;

    auto search_start = input.cbegin();
    while (regex_search(search_start, input.cend(), match, valid_mul)) {
        
        int x = stoi(match[1]);
        int y = stoi(match[2]);
        
        total += x * y;

        search_start = match.suffix().first; 
        // Because for some reason there is no cbegin method :(
    }

    cout << total << endl;

}
