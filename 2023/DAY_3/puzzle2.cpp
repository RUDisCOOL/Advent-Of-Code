#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

void findNumbersInRow(int index, string &line, vector<int> &result) {
    for (int i = 0; i <= index + 1; i++) {

        string numString = "";
        int n, start = i, end = i;
        while (isdigit(line[i])) {
            numString += line[i];
            end = i;
            i++;
        }
        if (!numString.empty()) {
            n = stoi(numString);
            if (index >= start - 1 && index <= end + 1) {
                result.push_back(n);
            }
        }
    }
}

int searchAdjacentNumbers(int index, int row, vector<string> &vec) {
    vector<int> result;

    //? Search for numbers in the above row
    if (row > 0) {
        for (int i = index - 1; i <= index + 1; i++) {
            if (i >= 0 && i < vec[row].size() && isdigit(vec[row - 1][i])) {
                findNumbersInRow(index, vec[row - 1], result);
                break;
            }
        }
    }
    //? Search for numbers in the same row
    if ((index - 1 >= 0 && isdigit(vec[row][index - 1])) || (index + 1 < vec[row].size() && isdigit(vec[row][index + 1]))) {
        findNumbersInRow(index, vec[row], result);
    }

    //? Search for numbers in the bottom row
    if (row < vec.size() - 1) {
        for (int i = index - 1; i <= index + 1; i++) {
            if (i >= 0 && i < vec[row].size() && isdigit(vec[row + 1][i])) {
                findNumbersInRow(index, vec[row + 1], result);
                break;
            }
        }
    }
    if (result.size() == 2) {
        return result[0] * result[1];
    }
    return 0;
}

int main() {
    ifstream file("./input.txt");
    if (!file.is_open()) {
        cerr << "Error opening file!!\n";
        return 1;
    }
    string line;
    vector<string> vec;
    vec.reserve(140);
    //* MAIN LOGIC OF CODE
    while (getline(file, line)) {
        vec.push_back(line);
    }
    vec.shrink_to_fit();
    int sum = 0;
    for (int i = 0; i < vec.size(); i++) {
        string temp = vec[i];
        for (int j = 0; j < temp.size(); j++) {
            //? Finding a symbol
            if ((temp[j]) == '*') {
                sum += searchAdjacentNumbers(j, i, vec);
            }
        }
    }
    cout << sum;
    file.close();
    return 0;
}