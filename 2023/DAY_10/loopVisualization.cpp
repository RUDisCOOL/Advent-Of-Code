#include <algorithm>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

struct Location {
    int x;
    int y;

    bool operator==(const Location &otherLoc) const {
        return x == otherLoc.x && y == otherLoc.y;
    }
    bool operator!=(const Location &otherLoc) const {
        return !(*this == otherLoc);
    }
    Location operator+(const Location &otherLoc) const {
        return {x + otherLoc.x, y + otherLoc.y};
    }
};

int xSize;
int ySize;
vector<string> sketch;
static const unordered_map<char, Location> directionLocation = {
    {'N', {-1, 0}},
    {'E', {0, 1}},
    {'W', {0, -1}},
    {'S', {1, 0}},
};

static const unordered_map<char, vector<char>> pipeConnectionType = {
    {'F', {'E', 'S'}},
    {'|', {'N', 'S'}},
    {'J', {'W', 'N'}},
    {'L', {'E', 'N'}},
    {'7', {'W', 'S'}},
    {'-', {'E', 'W'}},
};

char findPipeTypeOfS(const Location &s) {
    //? Lambda Function to check the direction Can Be Connected to the current Pipe or Not
    auto checkDirection = [](char direction, const Location &loc) -> bool {
        static const unordered_map<char, vector<char>> validConnections = {
            {'N', {'|', '7', 'F'}},
            {'E', {'J', '7', '-'}},
            {'W', {'-', 'L', 'F'}},
            {'S', {'|', 'L', 'J'}},
        };
        Location current = directionLocation.at(direction) + loc;

        //? Inner Lambda Function to check if the Location is in Range or not
        auto locationInRange = [](const Location &loc) -> bool {
            return loc.x >= 0 && loc.x < xSize && loc.y >= 0 && loc.y < ySize;
        };

        if (locationInRange(current)) {
            vector<char> temp = validConnections.at(direction);
            if (find(temp.begin(), temp.end(), sketch[current.x][current.y]) != temp.end()) {
                return true;
            }
        }
        return false;
    };

    //? Checking all the symbols that S could possibly be
    const vector<char> types = {'F', 'J', 'L', '7', '-', '|'};
    for (const char &ch : types) {
        vector<char> temp = pipeConnectionType.at(ch);
        bool isBothConnected = true;
        for (const char &direction : temp) {
            if (!checkDirection(direction, s)) {
                isBothConnected = false;
            }
        }
        if (isBothConnected) {
            return ch;
        }
    }
    return '\0';
}

int main() {
    ifstream file("./test.txt");
    if (!file.is_open()) {
        cerr << "Error opening file!!\n";
        return 1;
    }
    //* MAIN LOGIC OF CODE
    string line;
    Location s;
    int x = 0;
    //? Generating the map from the given input
    while (file >> line) {
        sketch.push_back(line);
        int y = 0;
        //? Finding the location of 'S'
        for (const char &ch : line) {
            if (ch == 'S')
                s = {x, y};
            y++;
        }
        x++;
    }
    xSize = sketch.size();
    ySize = sketch[0].size();

    //? Returning what is the type of pipe 'S'
    char startPipeType = findPipeTypeOfS(s);
    sketch[s.x][s.y] = startPipeType;

    //? Loop Generation
    vector<vector<char>> loop(xSize, vector<char>(ySize, ' '));

    //? Iterating to next pipes until we reach the starting point again
    Location prev = s;
    Location current = s;
    int loopLength = 0;
    do {
        char currentPipe = sketch[current.x][current.y];
        loop[current.x][current.y] = currentPipe;
        Location temp = current;
        Location loc0 = current + directionLocation.at(pipeConnectionType.at(currentPipe)[0]);
        Location loc1 = current + directionLocation.at(pipeConnectionType.at(currentPipe)[1]);
        if (loc0 == prev) {
            current = loc1;
        } else {
            current = loc0;
        }
        prev = temp;
        loopLength++;
    } while (current != s);

    loop[s.x][s.y] = 'S';

    //? Writing into the output file
    ofstream outFile("./loop.txt");
    if (!outFile.is_open()) {
        cerr << "Error opening output file";
        return 1;
    }

    for (vector x : loop) {
        for (char ch : x) {
            outFile << ch;
        }
        outFile << '\n';
    }

    cout << loopLength;
    file.close();
    return 0;
}