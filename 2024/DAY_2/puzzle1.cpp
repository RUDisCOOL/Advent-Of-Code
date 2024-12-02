#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

bool checkSafe(const vector<int> &vec) {
    bool isSafe = true;

    // # Checking the condition if the vector is not empty and the element order is decreasing
    if (!vec.empty() && vec[0] > vec[1]) {
        for (int j = 0; j < vec.size() - 1; j++) {
            int a = vec[j], b = vec[j + 1], diff = abs(a - b);
            if (!(a > b && diff > 0 && diff < 4)) {
                isSafe = false;
                break;
            }
        }
    } else if (vec[0] < vec[1]) {
        for (int j = 0; j < vec.size() - 1; j++) {
            int a = vec[j], b = vec[j + 1], diff = abs(a - b);
            if (!(a < b && diff > 0 && diff < 4)) {
                isSafe = false;
                break;
            }
        }
    } else {
        return false;
    }
    return isSafe;
}

int main() {
    ifstream file("./input.txt");
    if (!file.is_open()) {
        cerr << "Error opening file!!\n";
        return 1;
    }

    //* MAIN LOGIC OF CODE
    string line;
    int temp, x = 0;
    vector<vector<int>> reports;
    while (getline(file, line)) {
        stringstream ss(line);
        reports.push_back(vector<int>());
        while (ss >> temp) {
            reports[x].push_back(temp);
        }
        x++;
    }
    int sum = 0;
    for (const vector<int> &vec : reports) {
        if (checkSafe(vec)) {
            sum++;
        }
    }

    cout << sum;
    file.close();
    return 0;
}