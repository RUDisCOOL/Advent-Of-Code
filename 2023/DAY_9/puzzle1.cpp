#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

void getHistoryValues(const string &line, vector<int> &history) {
    istringstream iss(line);
    int num;
    while (iss >> num) {
        history.push_back(num);
    }
}

void predictNextValue(vector<int> &history) {
    vector<int> currVec;
    bool isAllZero = true;
    for (int i = 1; i < history.size(); i++) {
        int diff = history[i] - history[i - 1];
        currVec.push_back(diff);
        if (diff != 0) {
            isAllZero = false;
        }
    }
    if (!isAllZero) {
        predictNextValue(currVec);
    }
    history.push_back(history.back() + currVec.back());
}

int main() {
    ifstream file("./input.txt");
    if (!file.is_open()) {
        cerr << "Error opening file!!\n";
        return 1;
    }
    string line;
    int sum = 0;
    while (getline(file, line)) {
        //* MAIN LOGIC OF CODE
        vector<int> history;
        getHistoryValues(line, history);
        predictNextValue(history);
        sum += history.back();
        //* Debugging Messages
        // for (const int &num : history) {
        //     cout << num << " ";
        // }
        // cout << endl;
    }
    cout << sum;

    file.close();
    return 0;
}