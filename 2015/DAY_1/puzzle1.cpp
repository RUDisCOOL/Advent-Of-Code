#include <fstream>
#include <iostream>
using namespace std;

int main() {
    ifstream file("./input.txt");
    if (!file.is_open()) {
        cerr << "Error opening file!!\n";
        return 1;
    }
    //* MAIN LOGIC OF CODE
    char ch;
    int floor = 0;
    while (file >> ch) {
        if (ch == '(') {
            floor++;
        } else {
            floor--;
        }
    }
    cout << floor;

    file.close();
    return 0;
}