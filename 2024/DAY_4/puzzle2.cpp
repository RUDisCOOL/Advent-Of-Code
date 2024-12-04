#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

bool checkCross(const vector<string> &data, const int &i, const int &j) {
    string str = {data[i - 1][j - 1], data[i - 1][j + 1], data[i + 1][j + 1], data[i + 1][j - 1]};
    static const vector<string> possibilities = {"SSMM", "MSSM", "MMSS", "SMMS"};
    for (const string &a : possibilities) {
        if (str == a) {
            return true;
        }
    }
    return false;
}

int findAllXMAS(const vector<string> &data) {
    int count = 0;
    for (int i = 1; i < data.size() - 1; i++) {
        for (int j = 1; j < data[i].size() - 1; j++) {
            if (data[i][j] == 'A') {
                if (checkCross(data, i, j)) {
                    count++;
                }
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

    // # Finding all possible X-MAS from one point
    cout << findAllXMAS(data);

    file.close();
    return 0;
}