#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
typedef vector<vi> vvi;
typedef vector<vii> vvii;
typedef complex<int> ci;
typedef complex<double> cd;
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
#define ins insert
#define endl '\n'
#define FOR(a, b, c) for (auto(a) = (b); (a) < (c); ++(a))
#define ROF(a, b, c) for (auto(a) = (b); (a) > (c); --(a))
#define F0R(a, b) FOR ((a), 0, (b))
#define R0F(a, b) ROF ((a), (b), -1)
#define FORI(a, b) for (auto(a) = (b).begin(); (a) != (b).end(); ++(a))
#define ROFI(a, b) for (auto(a) = (b).rbegin(); (a) != (b).rend(); ++(a))
#define CEIL(a, b) ((a) + (b)-1) / (b)
const int xd[4] = {0, 1, 0, -1}, yd[4] = {1, 0, -1, 0};
template <typename t>
bool ckmin(t& a, const t& b) {
    return a > b ? a = b, true : false;
}
template <typename t>
bool ckmax(t& a, const t& b) {
    return a < b ? a = b, true : false;
}

ll const p = 998244353;

ll binpow(ll a, ll b) {
    a %= p;
    ll res = 1;
    while (b > 0) {
        if (b & 1) res = res * a % p;
        a = a * a % p;
        b >>= 1;
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, k, m;
    cin >> n >> k >> m;
    vector<tuple<int, int, int>> ms(m);
    F0R (i, m) {
        int i1, i2, i3;
        cin >> i1 >> i2 >> i3;
        ms.eb(i1 - 1, i2 - 1, i3);
    }

    if (m == 0) {
        cout << binpow(2, k) * n % p << endl;
        return 0;
    }
    ll allans = 1;
    F0R (bit, k) {
        vii ones, zeroes;
        for (auto [l, r, v] : ms) {
            if ((v >> bit) & 1)
                ones.eb(l, r);
            else
                zeroes.eb(l, r);
        }
        vector<bool> free(n, true);

        if (!ones.empty()) {
            sort(ALL(ones));
            int start = ones[0].fi, end = ones[0].se;
            for (auto [l, r] : ones) {
                if (l - 1 <= end)
                    ckmax(end, r);
                else {
                    fill(free.begin() + start, free.begin() + end, false);
                    start = l;
                    end = r;
                }
            }
            fill(free.begin() + start, free.begin() + end, false);
        }

        ll ans = 1;
        for (auto [l, r] : zeroes) {
            ll frees = count(free.begin() + l, free.begin() + r + 1, true);
            cout << frees << endl;
            fill(free.begin() + l, free.begin() + r + 1, false);
            ans = ans * (binpow(2, frees) - 1) % p;
        }
        cout << "bit " << bit << ": " << ans << endl;
        ans = ans * binpow(2, count(ALL(free), true)) % p;
        allans = allans * ans % p;
    }

    cout << allans << endl;
    return 0;
}
