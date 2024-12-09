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
    string input;
    vector<string> disk;
    int blockId = 0;
    file >> input;

    for (int i = 0; i < input.size(); i++) {
        if (i % 2 == 0) {
            disk.insert(disk.end(), input[i] - '0', to_string(blockId));
            blockId++;
        } else {
            disk.insert(disk.end(), input[i] - '0', ".");
        }
    }
    int i = 0;
    int j = disk.size() - 1;
    while (j > i) {
        string &a = disk[i], &b = disk[j];
        if (b == ".") {
            j--;
            continue;
        } else if (a == ".") {
            swap(a, b);
            j--;
        }
        i++;
    }
    long sum = 0;
    int itr = 0;
    while (disk[itr] != ".") {
        sum += stoi(disk[itr]) * itr;
        itr++;
    }
    cout << sum << endl;
    file.close();
    return 0;
}