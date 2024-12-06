#include <algorithm>
#include <fstream>
#include <iostream>
#include <set>
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
    pair<int, int> guardLoc;
    // # Getting the starting location of GUARD
    bool guardFound = false;
    for (y = 0; y < map.size(); y++) {
        for (x = 0; x < map[y].size(); x++) {
            if (map[y][x] == '^') {
                guardLoc = {y, x};
                guardFound = true;
                break;
            }
        }
        if (guardFound) {
            break;
        }
    }
    int itr = 0, count = 0;
    // # Path Finding First
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
    map[guardLoc.first][guardLoc.second] = '^';
    // # Replacing every X with # and trying if a sequence forms?
    for (int i = 0; i < map.size(); i++) {
        for (int j = 0; j < map[i].size(); j++) {
            if (map[i][j] == 'X') {
                map[i][j] = '#';
                bool isLoop = false;
                set<pair<pair<int, int>, int>> visited;

                // # Resetting the location of x and y to the guard location
                y = guardLoc.first;
                x = guardLoc.second;
                itr = 0;

                // # While loop condition to check if no loop is formed and the current index is inside the bounds
                while (0 <= x && x < map[y].size() && 0 <= y && y < map.size() && !isLoop) {
                    if (map[y][x] == '#') {
                        y -= directions[itr].first;
                        x -= directions[itr].second;
                        // # Direction Changed
                        ++itr %= 4;
                    }
                    y += directions[itr].first;
                    x += directions[itr].second;
                    if (visited.find({{y, x}, itr}) != visited.end()) {
                        isLoop = true;
                    }
                    visited.insert({{y, x}, itr});
                }
                if (isLoop) {
                    count++;
                }
                map[i][j] = '.';
            }
        }
    }
    cout << count;
    file.close();
    return 0;
}