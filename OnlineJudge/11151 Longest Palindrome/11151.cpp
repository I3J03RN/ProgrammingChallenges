#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

typedef unsigned int uint;

uint getLongestPalindrome(string string) {
    vector<vector<uint>> table(string.length());

    for (uint i = string.length(), index = 0; i > 0; index++, --i) {
        table[index] = vector<uint>(i);
    }

    for (uint i = 0; i < string.length(); ++i) {
        table[i][0] = 1;
    }

    for (uint l = 0; l + 1 < string.length(); ++l) {
        table[l][1] = string[l] == string[l + 1] ? 2 : 1;
    }

    for (uint r = 2; r < string.length(); ++r) {
        for (uint l = 0; l + r < string.length(); ++l) {
            table[l][r] = max(
                {table[l][r - 1], table[l + 1][r - 1],
                 (string[l] == string[l + r] ? 2 : 0) + table[l + 1][r - 2]});
        }
    }

    return table.front().back();
}

int main() {
    uint n;

    string in;
    getline(cin, in);

    stringstream(in) >> n;

    while (n--) {
        string input;
        getline(cin, input);
        if (input.length() <= 1) {
            cout << input.length() << "\n";
        } else {
            cout << getLongestPalindrome(input) << "\n";
        }
    }

    return 0;
}
