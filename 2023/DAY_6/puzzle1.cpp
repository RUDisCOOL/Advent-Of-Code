#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

struct WinRaceRecord {
    int time;
    int distance;
};

void getNumber(string &line, vector<int> &numbers) {
    //? This function finds all the numbers in a line
    int i = 0;
    while (i < line.size()) {
        string numString = "";
        int n = 0;

        while (isdigit(line[i])) {
            numString += line[i];
            i++;
        }
        if (!numString.empty()) {
            n = stol(numString);
            numbers.push_back(n);
        }
        i++;
    }
}

void generateRaceRecords(vector<int> &raceTimes, vector<int> &raceDistances, vector<WinRaceRecord> &raceRecords) {
    for (int i = 0; i < raceTimes.size(); i++) {
        WinRaceRecord tempRecord = {raceTimes[i], raceDistances[i]};
        raceRecords.push_back(tempRecord);
    }
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
    vector<int> winTime;
    getNumber(line, winTime);

    //? Getting distances from line
    getline(file, line);
    vector<int> winDist;
    getNumber(line, winDist);

    //? Generate WinRaceRecord
    vector<WinRaceRecord> raceRecords;
    raceRecords.reserve(winTime.size());
    generateRaceRecords(winTime, winDist, raceRecords);

    int prod = 1;

    //? Find the total possibilities of Winning
    for (WinRaceRecord wrr : raceRecords) {
        int count = 0;
        //* Debugging messages
        // cout << wrr.time << "->" << wrr.distance << " ";
        for (int i = wrr.time / 2; i >= 0; i--) {
            int distance = i * (wrr.time - i);
            if (distance > wrr.distance) {
                count++;
            }
        }
        count *= 2;
        if (wrr.time % 2 == 0) {
            count--;
        }
        prod *= count;
        //* Debugging messages
        // cout << count << "\n";
    }
    cout << prod;

    file.close();
    return 0;
}