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

ll calc(ll a, ll b, ll c) {
    ll d1 = a - b;
    ll d2 = a - c;
    ll d3 = b - c;
    return d1 * d1 + d2 * d2 + d3 * d3;
}

void solve() {
    int nr, ng, nb;
    cin >> nr >> ng >> nb;
    vvi v(3);
    v[0] = vi(nr);
    v[1] = vi(ng);
    v[2] = vi(nb);
    F0R (i, nr)
        cin >> v[0][i];
    F0R (i, ng)
        cin >> v[1][i];
    F0R (i, nb)
        cin >> v[2][i];
    vii vs;
    vs.reserve(nr + ng + nb);
    F0R (i, 3)
        for (int j : v[i]) vs.eb(j, i);
    sort(ALL(vs));
    F0R (i, 3)
        sort(ALL(v[i]));
    ll best = numeric_limits<ll>::max();

    for (auto [val, in] : vs) {
        auto it1 = lower_bound(ALL(v[(in + 1) % 3]), val);
        auto it2 = upper_bound(ALL(v[(in + 2) % 3]), val);
        if (it1 != v[(in + 1) % 3].end()) {
            if (it2 != v[(in + 2) % 3].begin()) --it2;
            ckmin(best, calc(val, *it1, *it2));
        }
        it1 = upper_bound(ALL(v[(in + 1) % 3]), val);
        it2 = lower_bound(ALL(v[(in + 2) % 3]), val);
        if (it2 != v[(in + 2) % 3].end()) {
            if (it1 != v[(in + 1) % 3].begin()) --it1;
            ckmin(best, calc(val, *it1, *it2));
        }
    }

    cout << best << endl;
}

int main() {
    ios_base::sync_with_stdio(0);
    cout.tie(0);

    int tt;
    cin >> tt;
    while (tt--) solve();

    return 0;
}
