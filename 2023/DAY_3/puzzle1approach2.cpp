#include <algorithm>
#include <fstream>
#include <iostream>
#include <unordered_set>
#include <vector>
using namespace std;

bool isSymbol(char ch) {
    static const unordered_set<char> symbols = {'/', '@', '#', '$', '%', '&', '*', '-', '+', '='};
    return symbols.find(ch) != symbols.end();
}

void findNumbersInRow(int index, string &line, int &sum) {
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
                sum += n;
            }
        }
    }
}

int searchAdjacentNumbers(int index, int row, vector<string> &vec) {
    int sum = 0;
    //? Search for numbers in the above row
    if (row > 0) {
        for (int i = index - 1; i <= index + 1; i++) {
            if (i >= 0 && i < vec[row].size() && isdigit(vec[row - 1][i])) {
                findNumbersInRow(index, vec[row - 1], sum);
                break;
            }
        }
    }
    //? Search for numbers in the same row
    if ((index - 1 >= 0 && isdigit(vec[row][index - 1])) || (index + 1 < vec[row].size() && isdigit(vec[row][index + 1]))) {
        findNumbersInRow(index, vec[row], sum);
    }

    //? Search for numbers in the bottom row
    if (row < vec.size() - 1) {
        for (int i = index - 1; i <= index + 1; i++) {
            if (i >= 0 && i < vec[row].size() && isdigit(vec[row + 1][i])) {
                findNumbersInRow(index, vec[row + 1], sum);
                break;
            }
        }
    }

    return sum;
}

int main() {
    ifstream file("./input.txt");
    if (!file.is_open()) {
        cerr << "Error opening file!!\n";
        return 1;
    }
    string line;

    int totalLine = count(istreambuf_iterator<char>(file), istreambuf_iterator<char>(), '\n') + 1;
    file.clear();
    file.seekg(0, ios::beg);

    vector<string> vec;
    vec.reserve(totalLine);
    //* MAIN LOGIC OF CODE
    while (getline(file, line)) {
        vec.push_back(line);
    }
    int sum = 0;
    for (int i = 0; i < vec.size(); i++) {
        string temp = vec[i];
        for (int j = 0; j < temp.size(); j++) {
            //? Finding a symbol
            if (isSymbol(temp[j])) {
                sum += searchAdjacentNumbers(j, i, vec);
            }
        }
    }
    cout << sum;
    file.close();
    return 0;
}