#include <fstream>
#include <iostream>
#include <unordered_set>
#include <vector>
using namespace std;

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
            string numString = "";
            int n;
            while (isdigit(line[i])) {
                numString += line[i];
                i++;
            }
            if (numString.size() > 0) {
                n = stoi(numString);
                winningList.insert(n);
            }
            i++;
        }

        //? Collecting my numbers from the data
        unordered_set<int> myNumbers;
        while (i < line.size()) {
            string numString = "";
            int n;
            while (isdigit(line[i])) {
                numString += line[i];
                i++;
            }
            if (numString.size() > 0) {
                n = stoi(numString);
                myNumbers.insert(n);
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