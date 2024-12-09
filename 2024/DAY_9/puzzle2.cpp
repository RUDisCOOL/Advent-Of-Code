#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

int main() {
    ifstream file("./input.txt");
    if (!file.is_open()) {
        cerr << "Error opening file!!\n";
        return 1;
    }
    string input;
    vector<pair<int, int>> disk;
    int blockId = 0;
    file >> input;

    for (int i = 0; i < input.size(); i++) {
        if (i % 2 == 0) {
            disk.push_back({blockId, input[i] - '0'});
            blockId++;
        } else {
            disk.push_back({-1, input[i] - '0'});
        }
    }
    int i = 0;
    int j = disk.size() - 1;
    while (j > i && j >= 0 && i < disk.size()) {
        if (disk[j].first == -1) {
            j--;
            continue;
        }
        while (j > i && j >= 0 && i < disk.size()) {
            if (disk[i].first == -1) {
                if (disk[i].second == disk[j].second) {
                    swap(disk[i], disk[j]);
                    break;
                } else if (disk[i].second > disk[j].second) {
                    disk.insert(disk.begin() + i + 1, pair<int, int>{-1, disk[i].second - disk[j++].second});
                    disk[i].second = disk[j].second;
                    swap(disk[i], disk[j]);
                    break;
                }
            }
            i++;
        }
        j--;
        i = 0;
    }
    long sum = 0;
    int itr = 0, index = 0;
    while (itr < disk.size()) {
        if (disk[itr].first != -1) {
            int start = index;
            int end = index + disk[itr].second;
            long sum_end = (long)(end - 1) * end / 2;
            long sum_start = (long)(start - 1) * start / 2;
            sum += disk[itr].first * (sum_end - sum_start);
            index = end;
        } else {
            index += disk[itr].second;
        }
        itr++;
    }
    cout << sum << endl;
    file.close();
    return 0;
}