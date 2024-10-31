#include <fstream>
#include <iostream>
#include <limits.h>
#include <unordered_map>
#include <vector>
using namespace std;

struct SeedRange {
    long start;
    long range;
};

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

void generateSeedMap(vector<SeedRange> &seedRanges, vector<vector<MapRange>> &mapData) {
    //? This function generates all the properties required for the seed ranges
    for (int i = 0; i < mapData.size(); i++) {
        vector<MapRange> mapRanges = mapData[i];
        vector<SeedRange> outputSeedRanges;
        for (int j = 0; j < seedRanges.size(); j++) {
            SeedRange tempSeedRange = seedRanges[j];
            long startSeed = tempSeedRange.start, seedRange = tempSeedRange.range, lastSeed = startSeed + seedRange - 1;
            bool rangeExists = false;
            //* Debugging Messages
            // cout << tempSeedRange.start << " " << tempSeedRange.range << " -> ";
            for (MapRange tempMapRange : mapRanges) {
                long startSource = tempMapRange.source, mapRange = tempMapRange.range, lastSource = startSource + mapRange - 1, destStart = tempMapRange.dest;
                SeedRange value;
                if (startSeed >= startSource) {
                    if (lastSeed <= lastSource) {
                        //? Seed range exists inside the map range
                        //? Only one range will be formed AND There will be no sub ranges
                        value.start = (startSeed - startSource) + destStart;
                        value.range = seedRange;
                        (startSeed - startSource) + destStart;
                    } else if (startSeed <= lastSource) {
                        //? Seed range starts from startSeed and it exists partially
                        //? Also, there can be only maximum of 2 sub ranges and minimum of 1 range
                        value.start = (startSeed - startSource) + destStart;
                        value.range = lastSource - startSeed + 1;
                        SeedRange temp;
                        temp.start = lastSource + 1;
                        temp.range = seedRange - (lastSource - startSeed + 1);
                        seedRanges.push_back(temp);
                    } else {
                        //? Seed range does not exist
                        continue;
                    }
                } else if (lastSeed >= startSource && lastSeed <= lastSource) {
                    //? Seed range does not start from the startSeed but it exists
                    //? Also, there can be only maximum of 2 sub ranges and minimum of 1 range
                    value.start = destStart;
                    value.range = lastSeed - startSource + 1;
                    SeedRange temp;
                    temp.start = startSeed;
                    temp.range = startSource - startSeed;
                    seedRanges.push_back(temp);
                } else if (startSeed < startSource && lastSeed > lastSource) {
                    //? Seed range exists in between start and end
                    //? Also, there will be 3 sub ranges
                    value.start = startSource;
                    value.range = mapRange;
                    SeedRange temp;
                    temp.start = startSeed;
                    temp.range = startSource - startSeed;
                    seedRanges.push_back(temp);
                    temp.start = lastSource + 1;
                    temp.range = seedRange - (lastSource - startSeed + 1);
                    seedRanges.push_back(temp);
                } else {
                    //? Seed range does not exist
                    continue;
                }
                rangeExists = true;
                outputSeedRanges.push_back(value);
                break;
            }
            if (!rangeExists) {
                outputSeedRanges.push_back(tempSeedRange);
            }
            //* Debugging Messages
            // for (int k = 0; k < outputSeedRanges.size(); k++) {
            //     SeedRange sr = outputSeedRanges[k];
            //     cout << sr.start << "-" << sr.range << " ";
            // }
            // cout << endl;
        }
        seedRanges = outputSeedRanges;
        //* Debugging Messages
        // cout << endl;
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

    //? Generate Seed Ranges
    vector<SeedRange> seedRanges;
    SeedRange tempSeedRange;
    for (int i = 0; i < seeds.size(); i++) {
        if (i % 2 == 0) {
            tempSeedRange.start = seeds[i];
            i++;
        }
        tempSeedRange.range = seeds[i];
        seedRanges.push_back(tempSeedRange);
    }

    //? Generate Map Data
    getMapData(mapData, file);

    //? Generate Seed Map
    generateSeedMap(seedRanges, mapData);

    //? Finding Min Location
    long min = LONG_MAX;
    for (SeedRange sr : seedRanges) {
        if (sr.start < min) {
            min = sr.start;
        }
    }
    cout << min << " ";

    file.close();
    return 0;
}