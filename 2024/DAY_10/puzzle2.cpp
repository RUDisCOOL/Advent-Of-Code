#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <vector>

using namespace std;

map<char, set<pair<int, int>>> freqMap;
map<pair<int, int>, int> visited;

void findPath(char ch) {
    if (ch == '9') {
        for (const pair<int, int> &coords : freqMap[ch]) {
            visited[coords] = 1;
        }
        return;
    }
    for (const pair<int, int> &coords : freqMap[ch]) {
        if (visited.find(coords) != visited.end()) {
            return;
        }
        int count = 0;

        // # Neighbouring Nodes
        static vector<pair<int, int>> adjacent = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
        for (const pair<int, int> &dir : adjacent) {
            pair<int, int> temp = {coords.first + dir.first, coords.second + dir.second};
            if (freqMap[ch + 1].find(temp) != freqMap[ch + 1].end()) {
                if (visited.find(temp) != visited.end()) {
                    count += visited[temp];
                } else {
                    findPath(ch + 1);
                    count += visited[temp];
                }
            }
        }

        visited[coords] = count;
    }
}

int main() {
    ifstream file("./input.txt");
    if (!file.is_open()) {
        cerr << "Error opening file!!\n";
        return 1;
    }
    //* MAIN LOGIC OF CODE
    string line;
    vector<string> input;
    int y = 0, x = 0;
    while (file >> line) {
        x = 0;
        for (const char &ch : line) {
            freqMap[ch].insert({y, x});
            x++;
        }
        input.push_back(line);
        y++;
    }
    // * DEBUG MESSAGES
    // for (const auto &a : freqMap) {
    //     cout << a.first << "->";
    //     for (const auto &b : a.second) {
    //         cout << "{" << b.first << "," << b.second << "}";
    //     }
    //     cout << endl;
    // }

    findPath('0');
    int count = 0;
    for (const pair<int, int> &a : freqMap['0']) {
        count += visited[a];
    }
    // * DEBUG MESSAGES
    // for (const auto &a : visited) {
    //     cout << "{" << a.first.first << "," << a.first.second << "} -> " << a.second << endl;
    // }

    cout << count;
    file.close();
    return 0;
}