#include <algorithm>
#include <fstream>
#include <iostream>
#include <unordered_map>
using namespace std;

int main() {
    ifstream file("./input.txt");
    if (!file.is_open()) {
        cerr << "Error opening file!!\n";
        return 1;
    }

    //* MAIN LOGIC OF CODE
    int num1, num2;
    unordered_map<int, int> count1, count2;

    while (file >> num1 >> num2) {
        count1[num1]++;
        count2[num2]++;
    }

    int sum = 0;
    for (const auto &a : count1) {
        sum += a.first * count2[a.first] * count1[a.first];
    }   

    cout << sum;
    file.close();
    return 0;
}