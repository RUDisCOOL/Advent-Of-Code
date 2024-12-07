#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

int countDigit(const long &num) {
    return floor(log10(num) + 1);
}

bool isValid(const long &test, const vector<long> &nums) {
    // # Generate sequence for num.size()-1
    int totalPossibilities = pow(3, nums.size() - 1);
    for (int i = 0; i < totalPossibilities; i++) {
        vector<long> numsCopy = nums;
        int n = i;
        for (int j = 0; j < nums.size() - 1; j++) {
            int temp = numsCopy[j + 1];
            if (n % 3 == 0) {
                numsCopy[j + 1] = temp + numsCopy[j];
            } else if (n % 3 == 1) {
                numsCopy[j + 1] = temp * numsCopy[j];
            } else {
                numsCopy[j + 1] = numsCopy[j] * pow(10, countDigit(temp)) + temp;
            }
            n /= 3;
        }
        if (numsCopy[numsCopy.size() - 1] == test) {
            return true;
        }
    }
    return false;
}

int main() {
    ifstream file("./input.txt");
    if (!file.is_open()) {
        cerr << "Error opening file!!\n";
        return 1;
    }
    //* MAIN LOGIC OF CODE
    string line;
    long count = 0;
    while (getline(file, line)) {
        stringstream lineStream(line);
        char ch;
        long test, num;
        vector<long> nums;
        lineStream >> test >> ch;
        while (lineStream >> num) {
            nums.push_back(num);
        }
        if (isValid(test, nums)) {
            count += test;
        }
    }

    cout << count;
    file.close();
    return 0;
}