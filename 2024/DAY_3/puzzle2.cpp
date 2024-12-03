#include <algorithm>
#include <fstream>
#include <iostream>
#include <regex>
#include <vector>
using namespace std;

bool isNumber(const string &str) {
    for (const char &ch : str) {
        if (!isdigit(ch)) {
            return false;
        }
    }
    return true;
}

int main() {
    ifstream file("./input.txt");
    if (!file.is_open()) {
        cerr << "Error opening file!!\n";
        return 1;
    }
    //* MAIN LOGIC OF CODE
    string line;

    static const regex reg("(mul\\(([0-9]{1,3}),([0-9]{1,3})\\))|(don't\\(\\))|(do\\(\\))");
    smatch match;
    int sum = 0;
    vector<string> stringIndexes;
    while (getline(file, line)) {
        while (regex_search(line, match, reg)) {
            if (match[1].matched) {
                stringIndexes.push_back(to_string(stoi(match[2]) * stoi(match[3])));
            } else {
                stringIndexes.push_back(match[0]);
            }
            line = match.suffix();
        }
    }
    bool flag = true;
    for (const string &tup : stringIndexes) {
        if (flag && isNumber(tup)) {
            sum += stoi(tup);
        } else if (tup == "don't()") {
            flag = false;
        } else if (tup == "do()") {
            flag = true;
        }
    }
    cout << sum;
    file.close();
    return 0;
}