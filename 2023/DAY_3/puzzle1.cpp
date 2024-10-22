#include <algorithm>
#include <fstream>
#include <iostream>
#include <unordered_set>
#include <vector>
using namespace std;

int findNumbers(int &i, string &line) {
    string numString = "";
    int n;
    while (isdigit(line[i])) {
        numString += line[i];
        i++;
    }
    if (numString.size() > 0) {
        n = stoi(numString);
        return n;
    }
    return 0;
}

bool isSymbol(char ch) {
    static const unordered_set<char> symbols = {'/', '@', '#', '$', '%', '&', '*', '-', '+', '='};
    return symbols.find(ch) != symbols.end();
}

int searchAdjacentSymbols(int start, int end, int row, vector<string> &vec) {
    int count = 0;
    int size = vec[row].size();

    //? Lamda function for searching symbols in a row
    auto searchSymbolsInRow = [&](int rowIndex) {
        for (int i = start - 1; i <= end + 1; i++) {
            if (i >= 0 && i < size && isSymbol(vec[rowIndex][i])) {
                count++;
            }
        }
    };

    //? Search the row above
    if (row > 0) {
        searchSymbolsInRow(row - 1);
    }

    //? Search the same row
    if (start > 0 && isSymbol(vec[row][start - 1])) {
        count++;
    }
    if (end < size - 1 && isSymbol(vec[row][end + 1])) {
        count++;
    }

    //? Search the row below
    if (row < vec.size() - 1) {
        searchSymbolsInRow(row + 1);
    }

    // cout << count << " ";
    return count;
}

int main() {
    ifstream file("./input.txt");
    if (!file.is_open()) {
        cerr << "Error opening file!!\n";
        return 1;
    }
    string temp;

    int totalLine = count(istreambuf_iterator<char>(file), istreambuf_iterator<char>(), '\n') + 1;
    file.clear();
    file.seekg(0, ios::beg);

    vector<string> vec;
    vec.reserve(totalLine);

    //* MAIN LOGIC OF CODE
    while (getline(file, temp)) {
        vec.push_back(temp);
    }
    int sum = 0;
    for (int i = 0; i < vec.size(); i++) {
        string line = vec[i];
        for (int j = 0; j < line.size(); j++) {
            string numString = "";
            int n = 0;

            //? Finding a number in a line
            if (isdigit(line[j])) {
                int start = j;
                n = findNumbers(j, line);
                sum += n * searchAdjacentSymbols(start, j - 1, i, vec);
            }
        }
        // cout << "\n";
    }
    cout << sum;
    file.close();
    return 0;
}