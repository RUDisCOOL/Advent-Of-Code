#include <fstream>
#include <iostream>
#include <unordered_set>
#include <vector>
using namespace std;

void findNumbers(int &i, string &line, unordered_set<int> &list) {
    string numString = "";
    int n;
    while (isdigit(line[i])) {
        numString += line[i];
        i++;
    }
    if (numString.size() > 0) {
        n = stoi(numString);
        list.insert(n);
    }
}

int main() {
    ifstream file("./input.txt");
    if (!file.is_open()) {
        cerr << "Error opening file!!\n";
        return 1;
    }
    string line;
    int points = 0;
    while (getline(file, line)) {
        //* MAIN LOGIC OF CODE
        int size = line.size();
        int pointsPerGame = 0;

        //? Skipping until ':' is found
        int i = 0;
        while (line[i] != ':') {
            i++;
        }
        i++;

        //? Finding numbers for winning list
        unordered_set<int> winningList;
        while (line[i] != '|') {
            if (isdigit(line[i])) {
                findNumbers(i, line, winningList);
            }
            i++;
        }

        //? Collecting my numbers from the data
        unordered_set<int> myNumbers;
        while (i < line.size()) {
            if (isdigit(line[i])) {
                findNumbers(i, line, myNumbers);
            }
            i++;
        }

        //? Checking how many numbers are winning
        for (int win : winningList) {
            if (myNumbers.find(win) != myNumbers.end()) {
                if (pointsPerGame == 0) {
                    pointsPerGame = 1;
                } else {
                    pointsPerGame *= 2;
                }
            }
        }

        //? Points per game
        points += pointsPerGame;
        // cout << pointsPerGame << " ";
        // cout << "\n";
    }
    cout << points;
    file.close();
    return 0;
}