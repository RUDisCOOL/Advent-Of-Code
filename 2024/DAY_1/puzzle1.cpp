#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

int main() {
    ifstream file("./input.txt");
    if (!file.is_open()) {
        cerr << "Error opening file!!\n";
        return 1;
    }

    //* MAIN LOGIC OF CODE
    int num1, num2;
    vector<int> vec1, vec2;

    while (file >> num1 >> num2) {
        vec1.push_back(num1);
        vec2.push_back(num2);
    }

    sort(vec1.begin(), vec1.end());
    sort(vec2.begin(), vec2.end());

    int sum = 0;
    for (int i = 0; i < vec1.size(); i++) {
        sum += abs(vec1[i] - vec2[i]);
    }
    cout << sum;

    file.close();
    return 0;
}