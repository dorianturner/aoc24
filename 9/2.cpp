#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// Checksum function to calculate checksum based on positions and file ids
ll checksum(vector<pair<ll, ll>>& file_lengths, vector<ll>& free_space_lengths) {
    ll total_checksum = 0;
    ll position = 0;

    for (ll i = 0; i < file_lengths.size(); ++i) {
        ll file_size = file_lengths[i].first;
        ll file_id = file_lengths[i].second;

        for (ll j = 0; j < file_size; ++j) {
            total_checksum += position * file_id;
            position++;
        }

        if (i < free_space_lengths.size()) {
            position += free_space_lengths[i];
        }
    }
    return total_checksum;
}

// Print the disk map based on the file_lengths and free_space_lengths
string printmap(vector<pair<ll, ll>>& file_lengths, vector<ll>& free_space_lengths) {
    string fragmented;
    
    for (ll i = 0; i < file_lengths.size(); ++i) {
        ll file_size = file_lengths[i].first;
        ll file_id = file_lengths[i].second;

        for (ll j = 0; j < file_size; ++j) {
            fragmented.push_back('0' + file_id);
        }

        if (i < free_space_lengths.size()) {
            for (ll j = 0; j < free_space_lengths[i]; ++j) {
                fragmented.push_back('.');
            }
        }
        
    }

    return fragmented;
}

void defragment(vector<pair<ll, ll>>& file_lengths, vector<ll>& free_space_lengths) {
    // cout << printmap(file_lengths, free_space_lengths) << endl;
    for (ll i = file_lengths.size() - 1; i >= 0; --i) {
        ll file_size = file_lengths[i].first;
        ll file_id = file_lengths[i].second;

        // Look for the leftmost free space that can fit this file
        for (ll j = 0; j < i; ++j) {
            
            if (free_space_lengths[j] >= file_size) {
                
                // Insert new spaces 
                ll old_space = free_space_lengths[j];
                free_space_lengths[j] = 0;
                free_space_lengths.insert(free_space_lengths.begin() + j + 1, old_space - file_size);

                // Update old spaces by merging
                free_space_lengths[i + 1] += file_size;
                old_space = free_space_lengths[i + 1];
                free_space_lengths[i] += old_space;
                free_space_lengths.erase(free_space_lengths.begin() + i + 1);
                
                // Insert new block
                file_lengths.insert(file_lengths.begin() + j + 1, {file_size, file_id});

                // Remove old block
                file_lengths.erase(file_lengths.begin() + i + 1);

                // cout << printmap(file_lengths, free_space_lengths) << endl;
                break;
            }
        }
    }
}

int main() {
    ifstream fin("input.in");
    vector<ll> dmap;
    vector<pair<ll, ll>> file_lengths;
    vector<ll> free_space_lengths;

    string input;
    fin >> input;
    for (char c : input) {
        dmap.push_back(c - '0');
    }

    for (ll i = 0; i < dmap.size(); ++i) {
        if (i % 2 == 0) {
            file_lengths.push_back({dmap[i], i / 2});
        } else {
            free_space_lengths.push_back(dmap[i]);
        }
    }

    defragment(file_lengths, free_space_lengths);
    
    ll result = checksum(file_lengths, free_space_lengths);
    cout << result << endl;

    return 0;
}
