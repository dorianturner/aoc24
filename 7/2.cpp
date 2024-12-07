#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll concatenate(ll a, ll b) {
    ll power = 1;
    while (power <= b) power *= 10; // accounts for digits in b
    return a * power + b;
}

ll evaluate(const vector<int>& nums, const vector<char>& ops) {
    ll result = nums[0]; 
    for (size_t i = 0; i < ops.size(); ++i) {
        if (ops[i] == '+') {
            result += nums[i + 1];
        } else if (ops[i] == '*') {
            result *= nums[i + 1];
        } else if (ops[i] == '|') { 
            result = concatenate(result, nums[i + 1]);
        }
    }
    return result;
}

bool matchesGoal(const vector<int>& nums, ll goal) {
    ll n = nums.size() - 1;
    vector<char> ops(n);

    // Try all 3^n combinations
    for (int mask = 0; mask < pow(3, n); ++mask) {
        int temp_mask = mask;
        for (int i = 0; i < n; ++i) {
            int op_choice = temp_mask % 3;
            temp_mask /= 3;
            
            if (op_choice == 0) 
                ops[i] = '+';
            else if (op_choice == 1) 
                ops[i] = '*';
            else 
                ops[i] = '|';
        }
        
        if (evaluate(nums, ops) == goal) {
            return true;
        }
    }
    return false;
}


int main() {
    ifstream fin("input.in");

    vector<ll> goal_nums;
    vector<vector<int>> input_nums;

    string line;
    while (getline(fin, line)) {
        size_t colon_pos = line.find(':');
        if (colon_pos == string::npos) {
            cerr << "Error: Invalid line format - " << line << endl;
            continue;
        }

        ll goal = stoll(line.substr(0, colon_pos)); 
        goal_nums.push_back(goal);

        vector<int> nums;
        stringstream ss(line.substr(colon_pos + 1)); 
        int num;
        while (ss >> num) {
            nums.push_back(num); 
        }

        input_nums.push_back(nums); 
    }

    ll sum = 0;

    for (int i = 0; i < goal_nums.size(); ++i) {
        if (matchesGoal(input_nums[i], goal_nums[i])) {
            sum += goal_nums[i];
        }
    }
    
    cout << sum << endl;

    return 0;
}