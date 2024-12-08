#include <fstream>
#include <iostream>
#include <set>
#include <unordered_map>
#include <vector>
using namespace std;

inline bool checkBounds(const pair<int, int> &p1, const int &upperbound) {
    return (0 <= p1.first && p1.first < upperbound) && (0 <= p1.second && p1.second < upperbound);
}

int main() {
    ifstream file("./input.txt");
    if (!file.is_open()) {
        cerr << "Error opening file!!\n";
        return 1;
    }
    //* MAIN LOGIC OF CODE
    string line;
    vector<string> map;
    unordered_map<char, vector<pair<int, int>>> locations;
    int coord_y = 0, coord_x = 0;
    while (file >> line) {
        map.push_back(line);
        coord_x = 0;
        for (const char &ch : line) {
            if (ch != '.') {
                locations[ch].push_back({coord_y, coord_x});
            }
            coord_x++;
        }
        coord_y++;
    }
    // # Finding Antinodes
    set<pair<int, int>> antinodes;
    for (const auto &a : locations) {
        // cout << a.first << "-> { ";
        const vector<pair<int, int>> &coords = a.second;
        for (int i = 0; i < coords.size(); i++) {
            for (int j = i + 1; j < coords.size(); j++) {
                // # Calculating Antinode Location
                pair<int, int> nodeDist = {coords[i].first - coords[j].first, coords[i].second - coords[j].second};
                pair<int, int> antinode1 = {coords[i].first + nodeDist.first, coords[i].second + nodeDist.second};
                pair<int, int> antinode2 = {coords[j].first - nodeDist.first, coords[j].second - nodeDist.second};
                antinodes.insert(coords[i]);
                antinodes.insert(coords[j]);
                while (checkBounds(antinode1, map.size())) {
                    antinodes.insert(antinode1);
                    // cout << antinode1.first << "," << antinode1.second << "  ";
                    antinode1 = {antinode1.first + nodeDist.first, antinode1.second + nodeDist.second};
                }
                while (checkBounds(antinode2, map.size())) {
                    antinodes.insert(antinode2);
                    // cout << antinode2.first << "," << antinode2.second << "  ";
                    antinode2 = {antinode2.first - nodeDist.first, antinode2.second - nodeDist.second};
                }
            }
        }
        // cout << "}" << endl;
    }
    cout << antinodes.size();
    file.close();
    return 0;
}