#include <bits/stdc++.h>
using namespace std;
typedef long double ld;
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

vector<ld> lfac(2e5 + 10, 0);

ld choose(ll n, ll k) { return lfac[n] - lfac[k] - lfac[n - k]; }

void solve() {
    int w, h, l, u, r, d;
    cin >> w >> h >> l >> u >> r >> d;

    ld prop = 0;
    if (d < h) {
        ll len = d;
        F0R (i, l - 1)
            prop += pow(2.0, choose(len - 1 + i, i) - len - i);
    }
    if (r < w) {
        ld len = r;
        F0R (i, u - 1)
            prop += pow(2.0, choose(len - 1 + i, i) - len - i);
    }

    cout << fixed << setprecision(9) << prop << endl;
}

int main() {
    ios_base::sync_with_stdio(0);
    cout.tie(0);

    for (ll i = 2; i <= 2e5 + 2; ++i)
        lfac[i] = lfac[i - 1] + log2(static_cast<ld>(i));
    int tt;
    cin >> tt;
    FOR (t, 1, tt + 1) {
        cout << "Case #" << t << ": ";
        solve();
    }

    return 0;
}
