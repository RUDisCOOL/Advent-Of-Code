#include <cmath>
#include <fstream>
#include <iostream>
#include <map>
using namespace std;

int countDigit(const unsigned long long &num) {
    return floor(log10(num) + 1);
}

pair<unsigned long long, unsigned long long> splitStone(unsigned long long stone) {
    int digits = countDigit(stone);
    unsigned long long num2 = 0;
    for (int i = 0; i < digits / 2; i++) {
        num2 += (stone % 10) * pow(10, i);
        stone /= 10;
    }
    return {stone, num2};
}

map<unsigned long long, unsigned long long> blink(const map<unsigned long long, unsigned long long> &stones) {
    map<unsigned long long, unsigned long long> newStones;
    for (const pair<unsigned long long, unsigned long long> &stone : stones) {
        if (stone.first == 0) {
            newStones[1] += stone.second;
        } else if (countDigit(stone.first) % 2 == 0) {
            pair<unsigned long long, unsigned long long> temp = splitStone(stone.first);
            newStones[temp.first] += stone.second;
            newStones[temp.second] += stone.second;
        } else {
            newStones[stone.first * 2024] += stone.second;
        }
    }
    return newStones;
}

int main() {
    ifstream file("./input.txt");
    if (!file.is_open()) {
        cerr << "Error opening file!!\n";
        return 1;
    }
    //* MAIN LOGIC OF CODE
    unsigned long long stone;
    map<unsigned long long, unsigned long long> stonesCount;
    while (file >> stone) {
        stonesCount[stone]++;
    }
    for (int i = 0; i < 75; i++) {
        stonesCount = blink(stonesCount);
    }
    unsigned long long count = 0;
    for (const auto &a : stonesCount) {
        count += a.second;
    }
    cout << count;
    file.close();
    return 0;
}
