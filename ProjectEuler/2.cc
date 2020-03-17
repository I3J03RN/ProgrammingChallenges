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
    int sum = 0;
    ll a = 0, b = 1;
    while (a < 4000000) {
        if ((a & 1) == 0) sum += a;
        a += b;
        swap(a, b);
    }
    cout << sum << endl;
}
