#include <fstream>
#include <iostream>
using namespace std;

int main() {
    ifstream file("./input.txt");
    if (!file.is_open()) {
        cerr << "Error opening file!!\n";
        return 1;
    }
    string line;
    int size = line.size(), sum = 0, first = 0, last = 0;
    while (getline(file, line)) {
        //* MAIN LOGIC OF CODE
        int size = line.size();
        for (int i = 0; i < size; i++) {
            char temp = line[i];
            if (isdigit(temp)) {
                first = temp - '0';
                break;
            }
        }
        for (int i = size - 1; i >= 0; i--) {
            char temp = line[i];
            if (isdigit(temp)) {
                last = temp - '0';
                break;
            }
        }
        sum += (first * 10 + last);
    }
    cout << sum;
    file.close();
    return 0;
}