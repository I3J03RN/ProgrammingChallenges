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

const ll border = 1000010;

ll steps[border];

ll calc(ll n) {
    if (n >= border) return calc(n & 1 ? 3 * n + 1 : n >> 1) + 1;
    if (steps[n] != -1) return steps[n];
    return steps[n] = calc(n & 1 ? 3 * n + 1 : n >> 1) + 1;
}

int main() {
    memset(steps, -1, sizeof(steps));
    steps[0] = 2;
    steps[1] = 1;
    ll m = -1;
    ll mNum = -1;
    for (ll n = 0; n <= 1000000; ++n) {
        int steps = calc(n);
        if (m < steps) {
            m = steps;
            mNum = n;
        }
    }
    cout << mNum << endl;
}
