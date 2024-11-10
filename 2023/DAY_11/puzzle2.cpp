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

    //? Finding which rows are empty
    vector<int> emptyRows;
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
            emptyRows.push_back(i);
        }
    }

    //? Finding which columns are empty
    vector<int> emptyCols;
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
            emptyCols.push_back(i);
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

    //? Calculating the new coordinates or locations of the galaxies
    for (Location &loc : galaxies) {
        int countX = 0;
        int countY = 0;
        for (int j = 0; j < emptyRows.size(); j++) {
            int x = emptyRows[j];
            if (loc.x > x) {
                countX += 999999;
            } else {
                break;
            }
        }
        for (int j = 0; j < emptyCols.size(); j++) {
            int y = emptyCols[j];
            if (loc.y > y) {
                countY += 999999;
            } else {
                break;
            }
        }
        loc.x += countX;
        loc.y += countY;
    }

    long sum = 0;
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