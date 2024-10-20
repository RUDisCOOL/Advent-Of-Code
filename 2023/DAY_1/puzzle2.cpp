#include <fstream>
#include <iostream>
#include <map>
using namespace std;

int main() {
    ifstream file("./input.txt");
    if (!file.is_open()) {
        cerr << "Error opening file!!\n";
        return 1;
    }
    string line;
    int size = line.size(), sum = 0, first = 0, last = 0;
    map<string, int> numMap = {{"one", 1}, {"two", 2}, {"three", 3}, {"four", 4}, {"five", 5}, {"six", 6}, {"seven", 7}, {"eight", 8}, {"nine", 9}};
    while (getline(file, line)) {
        // * MAIN LOGIC OF CODE
        int size = line.size();

        // * FINDING THE FIRST 
        for (int i = 0; i < size; i++) {
            char temp = line[i];
            if (isdigit(temp)) {
                first = temp - '0';
                goto first;
            }
            for (int j = 2; j < 5; j++) {
                if (i + j > size - 1) {
                    break;
                }
                string currentWord = "";
                for (int k = i; k <= i + j; k++) {
                    currentWord += line[k];
                }

                if (numMap.find(currentWord) != numMap.end()) {

                    first = numMap[currentWord];
                    goto first;
                }
            }
        }
    first:

        for (int i = size - 1; i >= 0; i--) {
            char temp = line[i];
            if (isdigit(temp)) {
                last = temp - '0';
                goto last;
            }
            for (int j = 2; j < 5; j++) {
                if (i - j < 0) {
                    break;
                }
                string currentWord = "";
                for (int k = i; k >= i - j; k--) {
                    currentWord = line[k] + currentWord;
                }

                if (numMap.find(currentWord) != numMap.end()) {

                    last = numMap[currentWord];
                    goto last;
                }
            }
        }
    last:

        sum += (first * 10 + last);
        // cout << endl;
    }

    cout << sum;
    file.close();
    return 0;
}