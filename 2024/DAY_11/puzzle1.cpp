#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

int countDigit(const long &num) {
    return floor(log10(num) + 1);
}

void splitStone(vector<long> &newStones, long &stone) {
    int digits = countDigit(stone);
    long num2 = 0;
    for (int i = 0; i < digits / 2; i++) {
        num2 += (stone % 10) * pow(10, i);
        stone /= 10;
    }
    newStones.push_back(num2);
}

void blink(vector<long> &stones) {
    vector<long> newStones;
    for (long &stone : stones) {
        if (stone == 0) {
            stone = 1;
        } else if (countDigit(stone) % 2 == 0) {
            splitStone(newStones, stone);
        } else {
            stone *= 2024;
        }
    }
    stones.insert(stones.end(), newStones.begin(), newStones.end());
}

int main() {
    ifstream file("./input.txt");
    if (!file.is_open()) {
        cerr << "Error opening file!!\n";
        return 1;
    }
    //* MAIN LOGIC OF CODE
    long stone;
    vector<long> stones;
    while (file >> stone) {
        stones.push_back(stone);
    }
    for (int i = 0; i < 25; i++) {
        blink(stones);
    }
    cout << stones.size();
    file.close();
    return 0;
}