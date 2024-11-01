#include <algorithm>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

struct Hand {
    string cards;
    int bid;
    int type;
};

void getHands(ifstream &file, vector<Hand> &hands) {
    string line;
    while (getline(file, line)) {
        Hand tempHand;
        string tempCards = "", bidString = "";
        int i = 0;
        while (line[i] != ' ') {
            tempCards += line[i];
            i++;
        }
        tempHand.cards = tempCards;
        while (i < line.size()) {
            bidString += line[i];
            i++;
        }
        tempHand.bid = stoi(bidString);
        hands.push_back(tempHand);
    }
}

void generateHandType(vector<Hand> &hands) {

    for (Hand &temp : hands) {

        //? Finding the total occurrences
        unordered_map<char, int> charOccurrences;
        string cardString = temp.cards;
        for (int i = 0; i < cardString.size(); i++)
            charOccurrences[cardString[i]]++;

        //? Finding the Char with MAX occurrences and it is not 'J'
        //* "JJJJJ" is an edge-case;
        if (charOccurrences.find('J') != charOccurrences.end() && charOccurrences.size() > 1) {
            int max = 0;
            char maxChar = 'J';
            for (const auto &tempChar : charOccurrences) {
                if (tempChar.first != 'J' && tempChar.second > max) {
                    max = tempChar.second;
                    maxChar = tempChar.first;
                }
            }
            charOccurrences[maxChar] += charOccurrences['J'];
            charOccurrences.erase('J');
        }

        //? Finding the frequency of occurrences
        unordered_map<int, int> freqCount;
        for (auto key : charOccurrences)
            freqCount[key.second]++;

        //? Different Type matching conditions
        if (freqCount[5] == 1)
            temp.type = 1; //* 1) 5 same char
        else if (freqCount[4] == 1)
            temp.type = 2; //* 2) 4 same char and 1 unique
        else if (freqCount[3] == 1 && freqCount[2] == 1)
            temp.type = 3; //* 3) 3 same char and a pair of two char
        else if (freqCount[3] == 1)
            temp.type = 4; //* 4) 3 same char and 2 unique char
        else if (freqCount[2] == 2)
            temp.type = 5; //* 5) two pairs of 2 char and 1 unique char
        else if (freqCount[2] == 1)
            temp.type = 6; //* 6) 2 same char and 3 unique
        else
            temp.type = 7; //* 7) all unique char
    }
}

int main() {
    ifstream file("./input.txt");
    if (!file.is_open()) {
        cerr << "Error opening file!!\n";
        return 1;
    }
    //* MAIN LOGIC OF CODE

    //? Get the Hands from input
    vector<Hand> hands;
    getHands(file, hands);

    //? Generate the type for each hand
    generateHandType(hands);
    //?Sort Hands based in the type of each hand
    const vector<char> cardStrength = {'J', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'Q', 'K', 'A'};
    sort(hands.begin(), hands.end(), [&cardStrength](const Hand &a, const Hand &b) {
        if (a.type == b.type) {
            auto findCharIndex = [&cardStrength](const char &ch) {
                for (int i = 0; i < cardStrength.size(); i++) {
                    if (cardStrength[i] == ch)
                        return i;
                }
                return -1;
            };
            for (int i = 0; i < 5; i++) {
                char charA = a.cards[i], charB = b.cards[i];
                if (charA != charB)
                    return (findCharIndex(charA) < findCharIndex(charB));
            }
        }
        return a.type > b.type;
    });
    //* Debugging messages
    // for (Hand temp : hands) {
    //     cout << temp.cards << " " << temp.bid << " " << temp.type << "\n";
    // }
    // cout << endl;

    //? Finding the total winnings for all hands
    int sum = 0;
    for (int i = 0; i < hands.size(); i++) {
        Hand temp = hands[i];
        sum += temp.bid * (i + 1);
    }
    cout << sum;
    file.close();
    return 0;
}