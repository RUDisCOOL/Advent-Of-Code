#include <fstream>
#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

struct nextNodes {
    string left;
    string right;
};

void generateNavigationMap(ifstream &file, unordered_map<string, nextNodes> &map) {
    string line;
    while (getline(file, line)) {
        int i = 0;
        vector<string> tempNodes;
        tempNodes.reserve(3);
        while (i < line.size()) {
            string temp = "";
            while (isalpha(line[i])) {
                temp += line[i];
                i++;
            }
            if (!temp.empty()) {
                tempNodes.push_back(temp);
            }
            i++;
        }
        map[tempNodes[0]] = {tempNodes[1], tempNodes[2]};
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

    //? Generate Navigation Map
    unordered_map<string, nextNodes> navMap;
    generateNavigationMap(file, navMap);

    //? Find total moves required to reach the final node "ZZZ" from starting node "AAA"
    string currentNode = "AAA";
    int i = 0, count = 0;
    while (currentNode != "ZZZ") {

        if (instructions[i] == 'L') {
            currentNode = navMap[currentNode].left;
        } else {
            currentNode = navMap[currentNode].right;
        }
        count++;
        if (i == instructions.size() - 1) {
            i = 0;
            continue;
        }
        i++;
    }

    //* Debugging Messages
    // for (const auto &temp : navMap) {
    //     cout << temp.first << " -> (" << temp.second.left << " " << temp.second.right << ")\n";
    // }

    cout << count;
    file.close();
    return 0;
}