#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
typedef vector<vi> vvi;
typedef vector<vii> vvii;
#define FOR(a, b, c) for (auto(a) = (b); (a) < (c); ++(a))
#define FORI(a, b) for (auto(a) = (b).begin(); (a) != (b).end(); ++(a))

bool isPalindromical(int i) {
    string input = to_string(i);
    string rev = string(input.rbegin(), input.rend());
    // cout << input << ", " << rev;
    return rev == input;
}

int main() {
    vi digits;
    for (int i = 100; i <= 999; ++i)
        for (int j = 100; j <= 999; ++j) digits.push_back(i * j);
    sort(digits.begin(), digits.end(), greater<int>());
    for (int d : digits)
        if (isPalindromical(d)) {
            cout << d << endl;
            break;
        }
}
