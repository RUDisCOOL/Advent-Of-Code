#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

bool validSprings(const vector<int> &groups, const string &springs) {
    int count = 0;
    vector<int> tempGroups;
    for (int i = 0; i <= springs.size(); i++) {
        char ch = springs[i];
        if (ch == '#') {
            count++;
        } else if (count != 0) {
            tempGroups.push_back(count);
            count = 0;
        }
    }
    if (tempGroups.size() != groups.size()) {
        return false;
    }
    for (int i = 0; i < groups.size(); i++) {
        if (tempGroups[i] != groups[i]) {
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
    string line;
    int i = 0;
    vector<string> springs;
    vector<vector<int>> groups;

    //* MAIN LOGIC OF CODE
    while (file >> line) {
        if (i % 2 == 0) {
            string tempString = "";
            springs.push_back(line);
        } else {
            string numString = "";
            groups.push_back(vector<int>());
            for (int j = 0; j <= line.size(); j++) {
                char ch = line[j];
                if (isdigit(ch)) {
                    numString += ch;
                } else {
                    groups[i / 2].push_back(stoi(numString));
                    numString = "";
                }
            }
        }
        i++;
    }

    int sum = 0;

    for (i = 0; i < springs.size(); i++) {
        int countQuestionMarks = count(springs[i].begin(), springs[i].end(), '?');
        int totalPossibilities = pow(2, countQuestionMarks);

        //? Generating all the possible combinations for ??????
        string generation(countQuestionMarks, '.');
        for (int j = 0; j < totalPossibilities; j++) {
            string tempString = springs[i];
            bool dotFound = false;
            int k = 0;
            while (!dotFound && k < generation.size()) {
                if (generation[k] == '.') {
                    generation[k] = '#';
                    dotFound = true;
                } else {
                    generation[k] = '.';
                }
                k++;
            }

            //? Replacing the ????? with the pattern that we found
            int counter = 0;
            for (char &ch : tempString) {
                if (ch == '?') {
                    ch = generation[counter];
                    counter++;
                }
            }
            if (validSprings(groups[i], tempString))
                sum++;
        }
    }
    cout << sum;

    file.close();
    return 0;
}