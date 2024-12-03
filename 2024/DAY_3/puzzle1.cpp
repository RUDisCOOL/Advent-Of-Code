#include <algorithm>
#include <fstream>
#include <iostream>
#include <regex>
#include <vector>
using namespace std;

int main() {
    ifstream file("./input.txt");
    if (!file.is_open()) {
        cerr << "Error opening file!!\n";
        return 1;
    }
    //* MAIN LOGIC OF CODE
    string line;

    static const regex reg("mul\\(([0-9]{1,3}),([0-9]{1,3})\\)");
    smatch match;
    int sum = 0;
    while (getline(file, line)) {
        while (regex_search(line, match, reg)) {
            sum += stoi(match[1]) * stoi(match[2]);
            line = match.suffix();
        }
    }
    cout << sum;
    file.close();
    return 0;
}