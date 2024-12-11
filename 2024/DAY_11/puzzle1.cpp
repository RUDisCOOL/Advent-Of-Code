#include <cmath>
#include <forward_list>
#include <fstream>
#include <iostream>
using namespace std;

void printStones(const forward_list<long> &stones) {
    for (const long &stone : stones)
        cout << stone << " ";
    cout << endl;
}

int countDigit(const long &num) {
    return floor(log10(num) + 1);
}

void splitStone(forward_list<long> &stones, forward_list<long>::iterator &itr) {
    long stone = *itr;
    int digits = countDigit(stone);
    long num1 = 0, num2 = 0;
    for (int i = 0; i < digits / 2; i++) {
        num2 += (stone % 10) * pow(10, i);
        stone /= 10;
    }
    *itr = stone;
    stones.insert_after(itr, num2);
}

void blink(forward_list<long> &stones) {
    for (auto itr = stones.begin(); itr != stones.end(); ++itr) {
        if (*itr == 0) {
            *itr = 1;
        } else if (countDigit(*itr) % 2 == 0) {
            splitStone(stones, itr);
            ++itr;
        } else {
            *itr *= 2024;
        }
    }
}

int main() {
    ifstream file("./input.txt");
    if (!file.is_open()) {
        cerr << "Error opening file!!\n";
        return 1;
    }
    //* MAIN LOGIC OF CODE
    long stone;
    forward_list<long> stones;
    while (file >> stone) {
        stones.push_front(stone);
    }
    stones.reverse();
    // printStones(stones);

    for (int i = 0; i < 25; i++) {
        blink(stones);
        // printStones(stones);
    }
    cout << distance(stones.begin(), stones.end());
    file.close();
    return 0;
}