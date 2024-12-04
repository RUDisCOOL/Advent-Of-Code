#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

vector<string> generatePossibleStrings(const vector<string> &data, const int &i, const int &j) {
    bool top = i - 3 >= 0;
    bool left = j - 3 >= 0;
    bool right = j + 3 < data[i].size();
    bool bottom = i + 3 < data.size();
    vector<string> possibilities;
    // # Check Right
    if (right) {
        int n = i;
        string str = "";
        for (int m = j; m <= j + 3; m++) {
            str += data[n][m];
        }
        possibilities.push_back(str);
    }

    // # Check Left
    if (left) {
        int n = i;
        string str = "";
        for (int m = j; m >= j - 3; m--) {
            str += data[n][m];
        }
        possibilities.push_back(str);
    }

    // # Check Top
    if (top) {
        int m = j;
        string str = "";
        for (int n = i; n >= i - 3; n--) {
            str += data[n][m];
        }
        possibilities.push_back(str);
    }

    // # Check Bottom
    if (bottom) {
        int m = j;
        string str = "";
        for (int n = i; n <= i + 3; n++) {
            str += data[n][m];
        }
        possibilities.push_back(str);
    }

    // # Check TopRight
    if (top && right) {
        int n = i;
        string str = "";
        for (int m = j; m <= j + 3; m++, n--) {
            str += data[n][m];
        }
        possibilities.push_back(str);
    }

    // # Check BottomRight
    if (bottom && right) {
        int n = i;
        string str = "";
        for (int m = j; m <= j + 3; m++, n++) {
            str += data[n][m];
        }
        possibilities.push_back(str);
    }

    // # Check TopLeft
    if (top && left) {
        int n = i;
        string str = "";
        for (int m = j; m >= j - 3; m--, n--) {
            str += data[n][m];
        }
        possibilities.push_back(str);
    }

    // # Check BottomLeft
    if (bottom && left) {
        int n = i;
        string str = "";
        for (int m = j; m >= j - 3; m--, n++) {
            str += data[n][m];
        }
        possibilities.push_back(str);
    }
    return possibilities;
}

int findAllXMAS(const vector<string> &data) {
    int count = 0;
    for (int i = 0; i < data.size(); i++) {
        for (int j = 0; j < data[i].size(); j++) {
            if (data[i][j] == 'X') {
                vector<string> temp = generatePossibleStrings(data, i, j);
                for (const string &str : temp) {
                    if (str == "XMAS") {
                        count++;
                    };
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

    // # Finding all possible XMAS from one point
    cout << findAllXMAS(data);

    file.close();
    return 0;
}