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

#include "22.in"

ll alphaVal(const string& s) {
    ll sum = 0;
    for (char c : s) sum += toupper(c) - 'A' + 1;

    return sum;
}

int main() {
    sort(names.begin(), names.end());
    ll sum = 0;
    for (int i = 1; i <= names.size(); ++i) {
        cout << i << " -- " << names[i - 1] << ": " << alphaVal(names[i - 1])
             << endl;
        sum += i * alphaVal(names[i - 1]);
    }
    cout << sum << endl;
}
