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
    o << '{';
    for (auto it = c.begin(); it != c.end();)
        o << *it << (++it != c.end() ? ", " : "}");
    return o;
}
template <class a, class b>
ostream& operator<<(ostream& o, const pair<a, b>& p) {
    return o << '(' << p.fi << ", " << p.se << ')';
}

array<int, 10> ar{0b1110111, 0b0010010, 0b1011101, 0b1011011, 0b0111010,
                  0b1101011, 0b1101111, 0b1010010, 0b1111111, 0b1111011};

int best(int val, int use) {
    int best = -1;

    F0R (i, 10) {
        if (val & ~ar[i]) continue;
        if (__builtin_popcount(ar[i] & ~val) == use) best = i;
    }

    return best;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, k;
    cin >> n >> k;
    vector<int> digit(n);
    F0R (i, n) {
        bitset<8> bs;
        cin >> bs;
        digit[i] = bs.to_ulong();
    }
    vvi dp(n, vi(k + 1, -1));
    F0R (i, min(8, k + 1))
        dp[n - 1][i] = best(digit[n - 1], i);
    R0F (i, n - 2) {
        F0R (used, k + 1) {
            F0R (use, 8) {
                if (used - use < 0) continue;
                if (~dp[i + 1][used - use])
                    ckmax(dp[i][used], best(digit[i], use));
            }
        }
    }
    if (dp[0][k] == -1) {
        cout << -1 << endl;
        return 0;
    }
    int next = k;
    F0R (i, n - 1) {
        cout << dp[i][next];
        next -= __builtin_popcount(ar[dp[i][next]] & ~digit[i]);
    }
    cout << dp[n - 1][next] << endl;

    return 0;
}
