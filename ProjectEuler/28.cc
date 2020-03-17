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

int main() {
    ll sum = 1;
    for (ll i = 3; i <= 1001; i += 2) {
        for (ll j = i * i, c = 0; c < 4; ++c, j -= i - 1) sum += j;
    }
    cout << sum << endl;
}
