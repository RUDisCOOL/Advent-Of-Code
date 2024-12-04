#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

int countPossibleStrings(const vector<string> &data, const int &i, const int &j) {
    static const string xmas = "XMAS";
    int count = 0;
    // # All the possible 8 directions that we have to find XMAS
    static const vector<vector<int>> directions = {
        {0, 0, -1, 1, -1, 1, -1, 1}, // * dir_y (vertical)
        {1, -1, 0, 0, 1, 1, -1, -1}, // * dir_x (horizontal)
    };
    for (int k = 0; k < 8; k++) {
        const int &dir_y = directions[0][k];
        const int &dir_x = directions[1][k];
        bool flag = true;
        for (int itr = 1; itr < 4; itr++) {
            int y = i + itr * dir_y;
            int x = j + itr * dir_x;
            // # If the coordinates are not in Bound OR the string does not Match with XMAS
            if (!(x >= 0 && x < data[i].size() && y >= 0 && y < data.size()) || (data[y][x] != xmas[itr])) {
                flag = false;
                break;
            }
        }
        if (flag) {
            count++;
        }
    }
    return count;
}

int findAllXMAS(const vector<string> &data) {
    int count = 0;
    for (int i = 0; i < data.size(); i++) {
        for (int j = 0; j < data[i].size(); j++) {
            if (data[i][j] == 'X') {
                count += countPossibleStrings(data, i, j);
            }
        }
    }
    return count;
}

int main() {
    ifstream file("./input.txt");
    if (!file.is_open()) {
        cerr << "Error opening file!!\n";
        return 1;
    }
    //* MAIN LOGIC OF CODE
    string line;
    vector<string> data;
    while (file >> line) {
        data.push_back(line);
    }

    // # Finding all possible XMAS from one point
    cout << findAllXMAS(data);

    file.close();
    return 0;
}