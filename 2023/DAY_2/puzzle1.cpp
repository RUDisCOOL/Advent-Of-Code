#include <fstream>
#include <iostream>
using namespace std;

int main() {
    ifstream file("./input.txt");
    if (!file.is_open()) {
        cerr << "Error opening file!!\n";
        return 1;
    }
    string line;
    int id = 0, sum = 0;
    while (getline(file, line)) {
        int size = line.size();

        //* MAIN LOGIC OF CODE
        id++;
        int i = 0;
        bool ispossible = true;

        //? Skipping the GAME 1: part from the start
        while (line[i] != ':') {
            i++;
        }

        for (i; i < size; i++) {
            string numString = "";
            int num = 0;
            char color;

            //? Getting the number
            if (isdigit(line[i])) {
                for (i; i < size; i++) {
                    if (isdigit(line[i])) {
                        numString += line[i];
                    } else {
                        //? Parsing to INT
                        num = stoi(numString);
                        //? Getting the 1st character of COLOR
                        i++;
                        color = line[i];
                        // cout << num << color << " ";

                        if ((color == 'r' && num > 12) || (color == 'g' && num > 13) || (color == 'b' && num > 14)) {
                            ispossible = false;
                            goto end;
                        }

                        break;
                    }
                }
            }
        }
    end:
        if (ispossible) {
            sum += id;
        }
        // cout << endl;
    }
    cout << "sum = " << sum;

    file.close();
    return 0;
}