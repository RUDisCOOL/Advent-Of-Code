#include <algorithm>
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
    //* MAIN LOGIC OF CODE

    int totalCards = 0;
    int totalLine = count(istreambuf_iterator<char>(file), istreambuf_iterator<char>(), '\n') + 1;
    // cout << totalLine << " ";
    file.clear();
    file.seekg(0, ios::beg);
    vector<int> cardCopies(totalLine, 1);

    int cardNum = 0;
    while (getline(file, line)) {
        int size = line.size();
        int totalWinNumbersInCard = 0;

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
                totalWinNumbersInCard++;
            }
        }
        // cout << totalWinNumbersInCard << " ";

        //? Cards in Total received
        int currentCardCopies = cardCopies[cardNum];
        totalCards += currentCardCopies;

        //? Card Copies received based on the Cards
        cardNum++;
        for (int j = cardNum; (j < totalLine) && (totalWinNumbersInCard > 0); (j++) && (totalWinNumbersInCard--)) {
            cardCopies[j] += currentCardCopies;
        }
    }
    // cout << "\n";
    // for (int ele : cardCopies) {
    //     cout << ele << " ";
    // }
    // cout << "\n";
    cout << totalCards;
    file.close();
    return 0;
}