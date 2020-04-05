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

constexpr int maxN = 1e4 + 100;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    bitset<maxN> isPrime(true);
    isPrime[1] = false;
    vi primes;
    FOR (i, 2, 1e4 + 1) {
        if (isPrime[i]) {
            primes.pb(i);
            for (int j = i + i; j <= 1e4; j += i) isPrime[j] = false;
        }
    }
    int tcs;
    cin >> tcs;
    while (tcs--) {
        ll n, m;
        cin >> n >> m;
        ll g = 1;
        vector<bool> in(m + 1, false);
        F0R (i, n) {
            ll t;
            cin >> t;
            in[t] = true;
            g = gcd(g, t);
        }
        vii gcdPrimes;
        for (int p : primes) {
            if (g == 1) break;
            int cnt = 0;
            while (g % p == 0) {
                ++cnt;
                g /= p;
            }
            if (cnt) gcdPrimes.eb(p, cnt);
        }
        ll best = 1;
        ll bestnum = 1;
        for (ll i = 2; i <= m; ++i) {
            int j = i;
            ll t = 1;
            for (auto [p, cnt] : gcdPrimes) {
                while (cnt && j % p == 0) {
                    --cnt;
                    j /= p;
                }
                while (cnt) {
                    t *= p;
                    --cnt;
                }
            }

            if (!in[i] && ckmax(best, t * j)) bestnum = i;
        }

        cout << bestnum << endl;
    }

    return 0;
}
