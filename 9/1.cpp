#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll checksum(vector<int>& defragmented) {
    ll total_checksum = 0;
    for (int i = 0; i < defragmented.size(); ++i) {
        if (defragmented[i] != -1) {
            total_checksum += i * defragmented[i];
        }
    }
    return total_checksum;
}

vector<int> sort_dmap(vector<int> fragmented) {

    while (true) {
        int first_free_index = -1;
        for (int i = 0; i < fragmented.size(); ++i) {
            if (fragmented[i] == -1) {
                first_free_index = i;
                break;
            }
        }

        int last_file_index = -1;
        for (int i = fragmented.size() - 1; i >= 0; --i) { 
            if (fragmented[i] != -1) {
                last_file_index = i;
                break;
            }
        }

        if (first_free_index > last_file_index) break; 

        fragmented[first_free_index] = fragmented[last_file_index];
        fragmented[last_file_index] = -1;
    }

    return fragmented;
}




int main() {
    ifstream fin("input.in");
    vector<int> dmap;
    vector<int> files;
    vector<int> freespace;

    string input;
    fin >> input;

    for (char c : input) {
        dmap.push_back(c - '0');
    }


    // Splitting map into files and freespace
    for (int i = 0; i < dmap.size(); ++i) {
        if (i%2 == 0) {
            files.push_back(dmap[i]);
        } else {
            freespace.push_back(dmap[i]);
        }
    }

    vector<int> fragmented;
    int file_id = 0;
    for (int i = 0; i < files.size(); ++i) {
        int file_size = files[i];
        int free_size = 0;
        if (i < freespace.size()) {
            free_size = freespace[i];
        }

        for (int j = 0; j < file_size; ++j) {
            fragmented.push_back(file_id);
        }

        file_id++;

        for (int j = 0; j < free_size; ++j) {
            fragmented.push_back(-1);
        }
    }

    vector<int> defragmented = sort_dmap(fragmented);
    cout << checksum(defragmented) << endl;

}