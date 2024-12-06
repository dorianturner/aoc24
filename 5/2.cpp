#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

bool correctOrder(const vector<pair<int, int>>& prules, const vector<int>& page) {
    for (auto rule : prules) {
        int first = rule.first, second = rule.second;

        auto pos1 = find(page.begin(), page.end(), first);
        auto pos2 = find(page.begin(), page.end(), second);
        
        // Both should exist and first before second
        // Don't even need to use distance() as > smart enough with iterables
        if (pos1 != page.end() && pos2 != page.end() && pos1 > pos2) {
            return false; 
        }
    }
    return true;
}

bool comparePages(int a, int b, const vector<pair<int, int>>& prules) {
    if (correctOrder(prules, {a, b})) {
        return true;
    }
    return false;
}



int main() {
    ifstream fin("input.in");

    vector<pair<int, int>> prules;
    vector<vector<int>> pages;

    int first, second;
    char separator;

    while (fin >> first >> separator) {
        if (separator == '|') {
            fin >> second;
            prules.push_back({first, second});
        } else if (separator == ',') {
            vector<int> currentLine;
            currentLine.push_back(first);

            int page;
            while (fin >> page) {
                currentLine.push_back(page);
                if (fin.peek() == ',') {
                    fin.ignore(); 
                } else if (fin.peek() == '\n' || fin.peek() == EOF) {
                    break;
                }
            }
            pages.push_back(currentLine);
        }
    }

    pages.erase(
        remove_if(pages.begin(), pages.end(), [&](const vector<int>& page) {
            return correctOrder(prules, page);
        }),
        pages.end()
    );

    ll sum = 0;
    
    for (auto page : pages) {
        sort(page.begin(), page.end(), [&prules](int a, int b) {
            return comparePages(a, b, prules);
            }   
        );

        sum += page[(page.size() - 1) / 2];
    } 

    cout << sum << endl;

    return 0;
}