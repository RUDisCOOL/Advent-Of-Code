#include <fstream>
#include <iostream>
#include <set>
#include <unordered_map>
#include <vector>
using namespace std;

vector<string> field;
set<pair<int, int>> visited;

inline bool checkBounds(const pair<int, int> &coords, const int &size) {
    return 0 <= coords.first && coords.first < size && 0 <= coords.second && coords.second < size;
}

int findPerimeter(const vector<pair<int, int>> &regionBoundary, const char ch) {
    // # This function finds the PERIMETER of REGION BOUNDARY
    int peri = 0;
    static const vector<pair<int, int>> directions = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
    for (const pair<int, int> &coords : regionBoundary) {
        for (const pair<int, int> &dir : directions) {
            pair<int, int> temp = {coords.first + dir.first, coords.second + dir.second};
            if (!(checkBounds(temp, field.size()) && field[temp.first][temp.second] == ch)) {
                peri++;
            }
        }
    }
    return peri;
}

int findRegions(const pair<int, int> &coords, vector<pair<int, int>> &regionBoundary) {
    // # This function finds the elements of the REGION BOUNDARY and returns AREA
    if (visited.find(coords) != visited.end()) {
        return 0;
    }
    visited.insert(coords);
    int i = coords.first, j = coords.second, area = 1;
    char ch = field[i][j];
    bool isBoundary = false;
    static const vector<pair<int, int>> directions = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
    for (const pair<int, int> &dir : directions) {
        pair<int, int> temp = {i + dir.first, j + dir.second};
        if (checkBounds(temp, field.size()) && field[temp.first][temp.second] == ch) {
            area += findRegions(temp, regionBoundary);
        } else {
            isBoundary = true;
        }
    }
    if (isBoundary) {
        regionBoundary.push_back(coords);
    }
    return area;
}

int main() {
    ifstream file("./input.txt");
    if (!file.is_open()) {
        cerr << "Error opening file!!\n";
        return 1;
    }
    //* MAIN LOGIC OF CODE
    string line;
    while (file >> line) {
        field.push_back(line);
    }
    int result = 0;

    for (int i = 0; i < field.size(); i++) {
        for (int j = 0; j < field.size(); j++) {
            char ch = field[i][j];
            if (visited.find({i, j}) != visited.end()) {
                continue;
            }
            // * Getting the elements in the region boundary and also getting the TOTAL AREA of REGION
            vector<pair<int, int>> regionBoundary;
            int area = findRegions({i, j}, regionBoundary);

            // * Perimeter finding for the region
            int peri = findPerimeter(regionBoundary, ch);

            result += area * peri;
        }
    }
    cout << result;
    file.close();
    return 0;
}