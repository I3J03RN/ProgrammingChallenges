#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
typedef vector<vi> vvi;
typedef vector<vii> vvii;
#define fi first
#define se second
#define ALL(x) (x).begin(), (x).end()
#define RALL(x) (x).rbegin(), (x).rend()
#define pf push_front
#define eb emplace_back
#define pb push_back
#define mp make_pair
#define mt make_tuple
#define ge(a, b) get<(b)>((a))
#define SZ(x) (x).size()
#define ft front()
#define bk back()
#define endl '\n'
#define FOR(a, b, c) for (auto(a) = (b); (a) < (c); ++(a))
#define ROF(a, b, c) for (auto(a) = (b); (a) > (c); --(a))
#define F0R(a, b) FOR ((a), 0, (b))
#define R0F(a, b) ROF ((a), (b), -1)
#define CEIL(a, b) ((a) + (b)-1) / (b)
#define SET(a, b) memset((a), (b), sizeof(a))
#ifndef DEBUG
#define DEBUG 0
#endif
#define dout \
    if (DEBUG) std::cerr
const int xd[4] = {0, 1, 0, -1}, yd[4] = {1, 0, -1, 0};
template <typename t>
bool ckmin(t& a, const t& b) {
    return a > b ? a = b, true : false;
}
template <typename t>
bool ckmax(t& a, const t& b) {
    return a < b ? a = b, true : false;
}

void solve() {
    ll n, l, r;
    cin >> n >> l >> r;
    ll pos = 1;
    int forbidden = 0;
    if (l > 2 * (n - 1)) {
        ++forbidden;
        pos = 2 * (n - 1);
        for (; l >= pos + 2 * (n - (forbidden + 1));
             pos += 2 * (n - ++forbidden))
            ;
    }
    int v = forbidden ? n : 1;
    int next = 0;
    while (pos <= r) {
        if (pos >= l) cout << v << ' ';
        if (v == n && forbidden != n - 1) {
            v = forbidden + 1;
            next = v + 1;
        } else if (v == forbidden + 1) {
            if (next == n) } else {
            next = v + 1;
            v = forbidden + 1;
        }

        ++pos;
    }
    cout << endl;
}

int main() {
    ios_base::sync_with_stdio(0);
    cout.tie(0);

    int tcs;
    cin >> tcs;
    while (tcs--) solve();
    return 0;
}