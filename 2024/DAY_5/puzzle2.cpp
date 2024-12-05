#include <fstream>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
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
    char temp;
    int num1, num2;
    unordered_map<int, unordered_set<int>> rules;
    while (getline(file, line)) {
        if (line.empty())
            break;
        stringstream stream(line);
        stream >> num1 >> temp >> num2;
        rules[num1].insert(num2);
    }
    int count = 0;
    while (getline(file, line)) {
        vector<int> update;
        stringstream stream(line);
        while (stream >> num1) {
            update.push_back(num1);
            stream >> temp;
        }
        bool flag = true;
        for (int i = 0; i < update.size(); i++) {
            int &a = update[i];
            for (int j = i + 1; j < update.size(); j++) {
                int &b = update[j];
                if (rules[b].find(a) != rules[b].end()) {
                    // # Swap b and a
                    int temp = b;
                    b = a;
                    a = temp;
                    flag = false;
                }
            }
        }
        if (!flag) {
            count += update[update.size() / 2];
        }
    }
    cout << count;
    file.close();
    return 0;
}