#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <vector>

using namespace std;

map<char, set<pair<int, int>>> freqMap;
map<pair<int, int>, set<pair<int, int>>> visited;

void findPath(char ch, pair<int, int> coords) {
    if (ch == '9') {
        visited[coords].insert(coords);
        return;
    }
    // # Neighbouring Nodes
    static vector<pair<int, int>> adjacent = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
    for (const pair<int, int> &dir : adjacent) {
        pair<int, int> temp = {coords.first + dir.first, coords.second + dir.second};
        if (freqMap[ch + 1].find(temp) != freqMap[ch + 1].end()) {
            if (visited.find(temp) != visited.end()) {
                visited[coords].insert(visited[temp].begin(), visited[temp].end());
            } else {
                findPath(ch + 1, temp);
                visited[coords].insert(visited[temp].begin(), visited[temp].end());
            }
        }
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

    int count = 0;
    for (const pair<int, int> &a : freqMap['0']) {
        findPath('0', a);
        count += visited[a].size();
    }
    // * DEBUG MESSAGES
    // for (const auto &a : visited) {
    //     cout << "{" << a.first.first << "," << a.first.second << "} -> ";
    //     for (const pair<int, int> &b : a.second) {
    //         cout << "{" << b.first << "," << b.second << "} ";
    //     }
    //     cout << endl;
    // }

    cout << count;
    file.close();
    return 0;
}