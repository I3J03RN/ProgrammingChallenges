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
#define SZ(x) (int)(x).size()
#define ft front()
#define bk back()
#define endl '\n'
#define FOR(a, b, c) for (auto(a) = (b); (a) < (c); ++(a))
#define ROF(a, b, c) for (auto(a) = (b); (a) > (c); --(a))
#define F0R(a, b) FOR ((a), 0, (b))
#define R0F(a, b) ROF ((a), (b), -1)
#define CEIL(a, b) ((a) + (b)-1) / (b)
#define SET(a, b) memset((a), (b), sizeof(a))
template <class t>
bool ckmin(t& a, const t& b) {
    return a > b ? a = b, true : false;
}
template <class t>
bool ckmax(t& a, const t& b) {
    return a < b ? a = b, true : false;
}
#ifndef DEBUG
#define DEBUG 0
#endif
#define dout \
    if (DEBUG) std::cerr
#define dvar(...) " [" << #__VA_ARGS__ ": " << (__VA_ARGS__) << "] "
template <class a, class b>
ostream& operator<<(ostream& o, const pair<a, b>& p);
template <class T>
struct IsC {
    template <class C>
    static char test(typename C::const_iterator*);
    template <class C>
    static int test(...);
    static const bool value = sizeof(test<T>(0)) == sizeof(char);
};
template <>
struct IsC<string> {
    static const bool value = false;
};
template <class C>
typename enable_if<IsC<C>::value, ostream&>::type operator<<(ostream& o,
                                                             const C& c) {
    o << '[';
    for (auto it = c.begin(); it != c.end();)
        o << *it << (++it != c.end() ? ", " : "");
    return o << ']';
}
template <class a, class b>
ostream& operator<<(ostream& o, const pair<a, b>& p) {
    return o << '(' << p.fi << ", " << p.se << ')';
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

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int h, w;
    cin >> h >> w;
    vector<vector<mod>> dp(h, vector<mod>(w));
    vector<vector<bool>> wall(h, vector<bool>(w));
    F0R (i, h) {
        char c;
        F0R (j, w) {
            cin >> c;
            wall[i][j] = c == '#';
        }
    }

    dp[h - 1][w - 1] = 1;
    R0F (i, h - 2)
        dp[i][w - 1] = wall[i][w - 1] ? 0 : dp[i + 1][w - 1];
    R0F (i, w - 2)
        dp[h - 1][i] = wall[h - 1][i] ? 0 : dp[h - 1][i + 1];

    R0F (i, h - 2)
        R0F (j, w - 2)
            if (!wall[i][j]) dp[i][j] = dp[i + 1][j] + dp[i][j + 1];

    cout << dp[0][0] << endl;

    return 0;
}
