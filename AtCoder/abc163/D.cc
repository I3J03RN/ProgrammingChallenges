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

struct mod {
    static const ll p = 1e9 + 7;
    ll val;
    mod() : val(0) {}
    mod(ll val) : val(val % p) {}
    mod operator+(mod o) { return mod(val + o.val); }
    mod operator-(mod o) { return mod(val - o.val + p); }
    mod operator*(mod o) { return mod(val * o.val); }
    mod operator/(mod o) { return mod(*this * pow(o, p - 2)); }
    static mod pow(mod a, mod b) {
        mod res = 1;
        for (; b.val; b.val >>= 1, a = a * a)
            if (b.val & 1) res = res * a;
        return res;
    }
    friend istream& operator>>(istream& i, mod& m) {
        i >> m.val;
        m.val %= mod::p;
        if (m.val < 0) m.val += mod::p;
        return i;
    }
    friend ostream& operator<<(ostream& o, mod m) { return o << m.val; }
};

ll sumft(ll a, ll b) { return (b + 1) * b / 2 - (a - 1) * a / 2; }

int main() {
    ios_base::sync_with_stdio(0);
    cout.tie(0);

    ll n, k;
    cin >> n >> k;
    mod ans;

    for (ll i = k; i <= n + 1; ++i) {
        ll plus = sumft(n - i + 1, n) - sumft(0, i - 1) + 1;
        dout << i << ": " << plus << endl;
        ans = ans + plus;
    }

    cout << ans << endl;
    return 0;
}
