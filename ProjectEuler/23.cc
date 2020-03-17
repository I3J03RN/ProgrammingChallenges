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

int sumDivs(int number) {
    if (number == 1) return 1;
    int sum = 0;
    int until = sqrt(number);
    for (int i = 1; i <= until; ++i)
        if (number % i == 0) {
            if (number / i == i)
                sum += i;
            else
                sum += i + number / i;
        }
    return sum - number;
}

int upperbound = 28123;

int main() {
    vi abus;
    for (int i = 1; i < upperbound; ++i)
        if (sumDivs(i) > i) abus.push_back(i);

    unordered_set<int> abusums;
    for (int i = 0; i < abus.size(); ++i)
        for (int j = i; j < abus.size(); ++j)
            if (abus[i] + abus[j] <= upperbound)
                abusums.insert(abus[i] + abus[j]);

    int sumsum = (upperbound * (upperbound + 1)) / 2;
    for (int i : abusums) sumsum -= i;

    cout << sumsum << endl;
}
