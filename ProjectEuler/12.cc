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

int numDivs(int number) {
    if (number == 1) return 1;
    int cnt = 0;
    int until = sqrt(number);
    for (int i = 1; i <= until; ++i)
        if (number % i == 0) cnt += 2;
    return cnt;
}

int main() {
    for (ll tria = 1, i = 2;; tria += i++) {
        // cout << tria << ": " << numDivs(tria) << endl;
        if (numDivs(tria) > 500) {
            cout << tria << endl;
            break;
        }
    }
}
