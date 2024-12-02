#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

bool checkSafe(const vector<int> &vec) {
    bool isSafe = true;
    // # Lambda Function to check that if the difference of all the 2 consecutive values is greater than 0 and smaller than 4
    auto diff = [](const vector<int> &vec) -> bool {
        for (int i = 0; i < vec.size() - 1; i++) {
            int diff = abs(vec[i] - vec[i + 1]);
            if (!(0 < diff && diff < 4)) {
                return false;
            }
        }
        return true;
    };

    if (diff(vec)) {
        // # If the record has differences in range (1,4) and is sorted in any one order then it is a Safe record
        if (is_sorted(vec.begin(), vec.end(), [](int a, int b) -> bool { return a < b; }))
            return true;
        else if (is_sorted(vec.begin(), vec.end(), [](int a, int b) -> bool { return a > b; }))
            return true;
    }
    return false;
}

bool isSafe(const vector<int> &vec) {
    // # Function to check that the given record is Safe if we only change any one level of the record
    for (int i = 0; i < vec.size(); i++) {
        vector<int> temp = vec;
        temp.erase(temp.begin() + i);
        if (checkSafe(temp)) {
            return true;
        }
    }
    return false;
}

int main() {
    ifstream file("./input.txt");
    if (!file.is_open()) {
        cerr << "Error opening file!!\n";
        return 1;
    }
    //* MAIN LOGIC OF CODE
    string line;
    int temp, x = 0, sum = 0;
    vector<int> reports;
    while (getline(file, line)) {
        stringstream ss(line);
        reports.clear();
        while (ss >> temp) {
            reports.push_back(temp);
        }
        if (checkSafe(reports)) {
            sum++;
        } else if (isSafe(reports)) {
            sum++;
        }
        x++;
    }

    cout << sum;
    file.close();
    return 0;
}