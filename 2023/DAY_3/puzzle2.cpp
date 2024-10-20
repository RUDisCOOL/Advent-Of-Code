#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

vector<int> findnumbers(int index, int row, vector<string> &vec) {
    string temp = vec[row];
    vector<int> result;
    for (int i = 0; i < temp.size(); i++) {
        if (isdigit(temp[i])) {
            int start = i;
            int end = i;
            string numString = "";
            int n = 0;
            for (i; i < temp.size(); i++) {
                if (isdigit(temp[i])) {
                    numString += temp[i];
                    end = i;
                    if (i == temp.size() - 1) {
                        n = stoi(numString);
                        if (index >= start - 1 && index <= end + 1) {
                            result.push_back(n);
                        }
                        break;
                    }
                } else {
                    n = stoi(numString);
                    end = i - 1;
                    if (index >= start - 1 && index <= end + 1) {
                        result.push_back(n);
                    }
                    break;
                }
            }
        }
    }
    result.shrink_to_fit();
    return result;
}

int searchnumbers(int index, int row, vector<string> &vec) {
    int prod = 1;
    // cout << vec[row][index];
    vector<int> result;
    vector<int> temp;

    //? Search for numbers in the above row
    if (row > 0) {
        for (int i = index - 1; i <= index + 1; i++) {
            if (i >= 0 && i < vec[row].size() && isdigit(vec[row - 1][i])) {
                //? Finding numbers in this ROW
                temp = findnumbers(index, row - 1, vec);
                for (int ele : temp) {
                    // cout << ele << " ";
                    result.push_back(ele);
                }
                break;
            }
        }
    }
    //? Search for numbers in the same row
    if ((index - 1 >= 0 && isdigit(vec[row][index - 1])) || (index + 1 < vec[row].size() && isdigit(vec[row][index + 1]))) {
        temp = findnumbers(index, row, vec);
        for (int ele : temp) {
            // cout << ele << " ";
            result.push_back(ele);
        }
    }

    //? Search for numbers in the bottom row
    if (row < vec.size() - 1) {
        for (int i = index - 1; i <= index + 1; i++) {
            if (i >= 0 && i < vec[row].size() && isdigit(vec[row + 1][i])) {
                //? Finding numbers in this ROW
                temp = findnumbers(index, row + 1, vec);
                for (int ele : temp) {
                    // cout << ele << " ";
                    result.push_back(ele);
                }
                break;
            }
        }
    }
    if (result.size() == 2) {
        for (int ele : result) {
            prod *= ele;
        }
        return prod;
    }
    return 0;
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
            //? Finding a symbol
            if ((temp[j]) == '*') {
                sum += searchnumbers(j, i, vec);
            }
        }
    }
    cout << sum;
    file.close();
    return 0;
}