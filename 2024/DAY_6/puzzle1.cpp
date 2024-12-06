#include <algorithm>
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
    //* MAIN LOGIC OF CODE
    string line;
    vector<string> map;
    while (file >> line) {
        map.push_back(line);
    }
    static const vector<pair<int, int>> directions = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
    int x = 0, y = 0;
    // # Getting the starting location of GUARD
    bool guardFound = false;
    for (y = 0; y < map.size(); y++) {
        for (x = 0; x < map[y].size(); x++) {
            if (map[y][x] == '^') {
                guardFound = true;
                break;
            }
        }
        if (guardFound) {
            break;
        }
    }
    int itr = 0, count = 0;
    while ((0 <= x && x < map[y].size()) && (0 <= y && y < map.size())) {
        if (map[y][x] == '#') {
            y -= directions[itr].first;
            x -= directions[itr].second;
            // # Direction Changed
            ++itr %= 4;
        }
        map[y][x] = 'X';
        y += directions[itr].first;
        x += directions[itr].second;
    }
    for (const string &str : map) {
        for (const char &ch : str) {
            if (ch == 'X')
                count++;
        }
    }
    cout << count;
    file.close();
    return 0;
}