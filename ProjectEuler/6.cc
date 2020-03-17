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
    ll sumqs = 0;
    for (ll i = 1; i <= 100; ++i) sumqs += i * i;
    ll qssum = 0;
    for (ll i = 1; i <= 100; ++i) qssum += i;
    qssum *= qssum;

    cout << qssum - sumqs << endl;
}
