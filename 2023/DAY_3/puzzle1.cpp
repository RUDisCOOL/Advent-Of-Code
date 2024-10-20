#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

bool issymbol(char ch) {
    vector<char> symbols = {'/', '@', '#', '$', '%', '&', '*', '-', '+', '='};
    for (char ele : symbols) {
        if (ch == ele) {
            return true;
        }
    }
    return false;
}

int searchsymbols(int start, int end, int row, vector<string> &vec) {
    int count = 0;
    int size = vec[row].size();
    //? Search the row above
    if (row > 0) {
        for (int i = start - 1; i <= end + 1; i++) {
            if (i >= 0 && i < size) {
                if (issymbol(vec[row - 1][i])) {
                    count++;
                }
            }
        }
    }

    //? Search the same row
    if (start > 0) {
        if (issymbol(vec[row][start - 1])) {
            count++;
        }
    }
    if (end < size - 1) {
        if (issymbol(vec[row][end + 1])) {
            count++;
        }
    }

    //? Search the row below
    if (row < vec.size() - 1) {
        for (int i = start - 1; i <= end + 1; i++) {
            if (i >= 0 && i < size) {
                if (issymbol(vec[row + 1][i])) {
                    count++;
                }
            }
        }
    }

    // cout << count << " ";
    return count;
}

int main() {
    ifstream file("./input.txt");
    if (!file.is_open()) {
        cerr << "Error opening file!!\n";
        return 1;
    }
    string line;
    vector<string> vec;
    vec.reserve(140);
    //* MAIN LOGIC OF CODE
    while (getline(file, line)) {
        vec.push_back(line);
    }
    vec.shrink_to_fit();
    int sum = 0;
    for (int i = 0; i < vec.size(); i++) {
        string temp = vec[i];
        for (int j = 0; j < temp.size(); j++) {
            string numString = "";
            int n = 0;

            //? Finding a number in a line
            if (isdigit(temp[j])) {
                int start = j;
                for (j; j < temp.size(); j++) {
                    if (isdigit(temp[j])) {
                        numString += temp[j];
                        if (j == temp.size() - 1) {
                            n = stoi(numString);
                            // cout << n << " ";
                            sum += n * searchsymbols(start, j, i, vec);
                            break;
                        }
                    } else {
                        n = stoi(numString);
                        // cout << n << " ";
                        sum += n * searchsymbols(start, j - 1, i, vec);
                        break;
                    }
                }
            }
        }
        // cout << "\n";
    }
    cout << sum;
    file.close();
    return 0;
}