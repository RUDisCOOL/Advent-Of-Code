#include <fstream>
#include <iostream>
#include <numeric>
#include <unordered_map>
#include <vector>
using namespace std;

struct nextNodes {
    string left;
    string right;
};

void generateNavigationMap(ifstream &file, vector<string> &startNodes, unordered_map<string, nextNodes> &map) {
    string line;
    while (getline(file, line)) {
        int i = 0;
        vector<string> tempNodes;
        tempNodes.reserve(3);
        while (i < line.size()) {
            string temp = "";
            while (isalnum(line[i])) {
                temp += line[i];
                i++;
            }
            if (!temp.empty()) {
                tempNodes.push_back(temp);
            }
            i++;
        }
        map[tempNodes[0]] = {tempNodes[1], tempNodes[2]};
        if (tempNodes[0][2] == 'A') {
            startNodes.push_back(tempNodes[0]);
        }
    }
}

int main() {
    ifstream file("./input.txt");
    if (!file.is_open()) {
        cerr << "Error opening file!!\n";
        return 1;
    }
    string instructions;
    getline(file, instructions);

    //? Removing the empty line
    string line;
    getline(file, line);

    //? Generate Navigation Map && Get startingNodes
    unordered_map<string, nextNodes> navMap;
    vector<string> startNodes;
    generateNavigationMap(file, startNodes, navMap);

    //? Getting the LCM for all the minimum steps required to reach final node
    long lcmNum = 1;
    for (string &currentNode : startNodes) {

        //? Find total moves required to reach the final node ENDING IN 'Z' and from starting node ending in 'A'
        int i = 0, count = 0;
        while (currentNode[2] != 'Z') {
            i = count % instructions.size();
            if (instructions[i] == 'L') {
                currentNode = navMap[currentNode].left;
            } else {
                currentNode = navMap[currentNode].right;
            }
            count++;
        }
        lcmNum = lcm(lcmNum, count);
    }
    // * Debugging Messages
    // for (const auto &temp : navMap) {
    //     cout << temp.first << " -> (" << temp.second.left << " " << temp.second.right << ")\n";
    // }

    cout << lcmNum << " ";
    file.close();
    return 0;
}