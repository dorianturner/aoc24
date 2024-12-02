#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

bool safe(vector<int>& report) {
    bool increasing = false, decreasing = false;

    for (int i = 1; i < report.size(); i++) {
        int diff = report[i] - report[i - 1];
        if (abs(diff) < 1 || abs(diff) > 3) return false; 
        
        if (diff > 0) {
            if (decreasing) return false;
            increasing = true;
        } else if (diff < 0) {
            if (increasing) return false;
            decreasing = true;
        }
    }

    return true;
}

bool safe_with_dampener(vector<int>& report) {
    if (safe(report)) return true;

    for (int i = 0; i < report.size(); i++) {
        vector<int> modified_report = report;
        modified_report.erase(modified_report.begin() + i); 
        if (safe(modified_report)) return true; 
    }

    return false;
}



int main() {
    ifstream fin("input.in"); 
    string line;
    int acc = 0;

    while (getline(fin, line)) {
        istringstream iss(line);
        vector<int> report;
        int num;

        while (iss >> num) {
            report.push_back(num);
            cout << num << endl;
        }

        if (safe_with_dampener(report)) {
            cout << "report is safe" << endl;
            acc++;
        }
    }

    cout << acc << endl;
    return 0;
}
