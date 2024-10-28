#include <fstream>
#include <iostream>
#include <limits.h>
#include <unordered_map>
#include <vector>
using namespace std;

struct MapRange {
    long source;
    long dest;
    long range;
};

void getNumbers(string &line, vector<long> &numbers) {
    //? This function finds all the numbers in a line
    int i = 0;
    while (i < line.size()) {
        string numString = "";
        long n = 0;

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

void getMapData(vector<vector<MapRange>> &mapData, ifstream &file) {
    //? This function gets all the Ranges of all Maps
    string line = "";
    int j = -1;
    while (getline(file, line)) {
        if (line.empty()) {
            getline(file, line);
            j++;
        } else {
            vector<long> temp;
            getNumbers(line, temp);

            MapRange tempMap;
            tempMap.dest = temp[0];
            tempMap.source = temp[1];
            tempMap.range = temp[2];

            mapData[j].push_back(tempMap);
        }
    }
}

void generateSeedMap(vector<long> &seeds, vector<vector<MapRange>> &mapData) {
    //? This function generates all the properties required for the seed
    for (int i = 0; i < mapData.size(); i++) {
        vector<MapRange> ranges = mapData[i];

        for (int i = 0; i < seeds.size(); i++) {
            long num = seeds[i];
            long value = num;
            bool valueFound = false;
            for (int j = 0; j < ranges.size(); j++) {
                MapRange temp = ranges[j];
                //? If the seed-number exists in the range
                if (num >= temp.source && num < (temp.source + temp.range)) {
                    //? We found the number corresponding to it in the mapData
                    value = temp.dest + (num - temp.source);
                    break;
                }
            }
            seeds[i] = value;
        }
    }
}

int main() {
    ifstream file("./input.txt");
    if (!file.is_open()) {
        cerr << "Error opening file!!\n";
        return 1;
    }
    string line, seedString;
    getline(file, seedString);

    //* MAIN LOGIC OF CODE
    vector<long> seeds;
    getNumbers(seedString, seeds);

    //? Initialize Map Data
    vector<MapRange> tempVec(0);
    vector<vector<MapRange>> mapData(7, tempVec);

    //? Generate Map Data
    getMapData(mapData, file);

    //? Generate Seed Map
    generateSeedMap(seeds, mapData);

    //? Finding Min Location
    long min = LONG_MAX;
    for (long ele : seeds) {
        if (ele < min)
            min = ele;
    }
    cout << min << " ";

    file.close();
    return 0;
}