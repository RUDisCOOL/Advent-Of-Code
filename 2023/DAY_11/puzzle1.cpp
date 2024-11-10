#include <cmath>
#include <fstream>
#include <iostream>
#include <list>
#include <vector>
using namespace std;

struct Location {
    int x;
    int y;
};

int main() {
    ifstream file("./input.txt");
    if (!file.is_open()) {
        cerr << "Error opening file!!\n";
        return 1;
    }
    string line;
    vector<string> space;
    while (file >> line) {
        //* MAIN LOGIC OF CODE
        space.push_back(line);
    }

    //? Inserting empty spaces horizontally
    for (int i = 0; i < space.size(); i++) {
        string tempString = space[i];
        bool isEmpty = true;
        for (int j = 0; j < tempString.size(); j++) {
            char ch = tempString[j];
            if (ch != '.') {
                isEmpty = false;
                break;
            }
        }
        if (isEmpty) {
            string temp(tempString.size(), '.');
            space.insert(space.begin() + i, temp);
            i++;
        }
    }

    //? Inserting empty spaces vertically
    for (int i = 0; i < space[0].size(); i++) {
        bool isEmpty = true;
        for (int j = 0; j < space.size(); j++) {
            char ch = space[j][i];
            if (ch != '.') {
                isEmpty = false;
                break;
            }
        }
        if (isEmpty) {
            for (int j = 0; j < space.size(); j++) {
                space[j].insert(space[j].begin() + i, '.');
            }
            i++;
        }
    }

    //? Finding all the galaxies in space
    vector<Location> galaxies;
    for (int i = 0; i < space.size(); i++) {
        string tempString = space[i];
        for (int j = 0; j < tempString.size(); j++) {
            char ch = tempString[j];
            if (ch == '#') {
                galaxies.push_back({i, j});
            }
        }
    }

    int sum = 0;
    for (int i = 0; i < galaxies.size() - 1; i++) {
        Location first = galaxies[i];
        for (int j = i + 1; j < galaxies.size(); j++) {
            Location second = galaxies[j];
            sum += abs(second.x - first.x) + abs(second.y - first.y);
        }
    }

    cout << sum;
    file.close();
    return 0;
}