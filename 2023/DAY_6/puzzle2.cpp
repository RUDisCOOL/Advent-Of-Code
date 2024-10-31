#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

struct WinRaceRecord {
    long time;
    long distance;
};

long getNumber(string &line) {
    //? This function finds all the numbers in a line
    int i = 0;
    string numString = "";
    while (i < line.size()) {
        if (isdigit(line[i])) {
            numString += line[i];
        }
        i++;
    }
    if (!numString.empty()) {
        return stol(numString);
    }
    return 0;
}

int main() {
    ifstream file("./input.txt");
    if (!file.is_open()) {
        cerr << "Error opening file!!\n";
        return 1;
    }
    //* MAIN LOGIC OF CODE
    string line;

    //? Getting time from the line
    getline(file, line);
    long winTime = getNumber(line);

    //? Getting distances from line
    getline(file, line);
    long winDist = getNumber(line);

    //? Generate WinRaceRecord
    WinRaceRecord raceRecord = {winTime, winDist};

    //? Find the total possibilities of Winning
    long count = 0;
    //* Debugging messages
    // cout << raceRecord.time << "->" << raceRecord.distance << "\n";
    for (long i = raceRecord.time / 2; i >= 0; i--) {
        long distance = i * (raceRecord.time - i);
        if (distance > raceRecord.distance) {
            count++;
        }
    }
    count *= 2;
    if (raceRecord.time % 2 == 0) {
        count--;
    }
    cout << count;

    file.close();
    return 0;
}