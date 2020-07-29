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

int main() {
    ios_base::sync_with_stdio(0);
    cout.tie(0);

    int tcs;
    cin >> tcs;
    while (tcs--) {
        int n;
        cin >> n;
        vector<ll> a(n), b(n);
        F0R (i, n)
            cin >> a[i] >> b[i];
        if (n == 1) {
            cout << a[0] << endl;
            continue;
        }
        vi bad;
        vector<bool> isGood(n, true);
        F0R (i, n)
            if (b[(n + i - 1) % n] < a[i]) bad.pb(i), isGood[i] = false;
        // for (int i : bad) cout << i << endl;
        // if (SZ(bad) == 0) cout << *min_element(ALL(a)) << endl;
        // else if (SZ(bad) == 1) {
        //     ll cost = a[bad[0]];
        //     ll extra = a[bad[0]] - b[(n + bad[0] - 1) % n];
        //     for (ll l : a) ckmin(cost, l + extra);
        //     cout << cost << endl;
        //}
        // else {
        ll cost = 0;
        ll m = numeric_limits<ll>::max();
        for (int i : bad) {
            cost += a[i] - b[(n + i - 1) % n];
            ckmin(m, b[(n + i - 1) % n]);
        }
        F0R (i, n) {
            if (isGood[i]) ckmin(m, a[i]);
        }
        cout << cost + m << endl;
        //}
    }

    return 0;
}
