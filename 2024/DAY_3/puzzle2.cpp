#include <algorithm>
#include <fstream>
#include <iostream>
#include <regex>
#include <vector>
using namespace std;

struct stringPos {
    string str;
    int index;
};

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
    vector<stringPos> stringIndexes;
    while (getline(file, line)) {
        int positionOffset = 0;
        while (regex_search(line, match, reg)) {
            positionOffset += match.position() + match[0].length();
            if (match[1].matched) {
                stringIndexes.push_back({to_string(stoi(match[2]) * stoi(match[3])), positionOffset});
            } else {
                stringIndexes.push_back({match[0], positionOffset});
            }
            line = match.suffix();
        }
    }
    bool flag = true;
    for (const stringPos &tup : stringIndexes) {
        // cout << tup.str << " " << tup.index << endl;
        if (flag && isNumber(tup.str)) {
            sum += stoi(tup.str);
        } else if (tup.str == "don't()") {
            flag = false;
        } else if (tup.str == "do()") {
            flag = true;
        }
    }
    cout << sum;
    file.close();
    return 0;
}