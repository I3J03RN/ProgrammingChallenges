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

template <bool print>
int length(int d) {
    int iteration = 1;
    map<int, int> res;
    int n = 1;
    while (n != 0) {
        while (d > n) n *= 10;
        if constexpr (print) cout << "  " << n << ": ";
        n %= d;
        if constexpr (print) cout << n << endl;
        auto it = res.find(n);
        if (it == res.end())
            res.insert(make_pair(n, iteration++));
        else {
            int firstit = it->second;
            return iteration - firstit;
        }
    }
    return 0;
}

int main() {
    int m = 0, n;
    for (int i = 1; i < 1000; ++i) {
        // cout << i << endl;
        int l = length<false>(i);
        if (l > m) {
            n = i;
            m = l;
        }
        // cout << i << ": " << l << endl;
    }
    cout << m << ": " << n << endl;
    length<true>(n);
}
