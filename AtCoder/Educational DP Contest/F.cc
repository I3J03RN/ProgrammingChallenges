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

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    string s, t;
    cin >> s >> t;
    int n = SZ(s), m = SZ(t);
    vvi dp(n + 1, vi(m + 1, 0));
    dp[n - 1][m - 1] = s[n - 1] == t[m - 1];
    R0F (i, n - 2)
        dp[i][m - 1] = s[i] == t[m - 1] ? 1 : dp[i + 1][m - 1];
    R0F (i, m - 2)
        dp[n - 1][i] = s[n - 1] == t[i] ? 1 : dp[n - 1][i + 1];
    R0F (i, n - 2)
        R0F (j, m - 2)
            dp[i][j] = max({dp[i + 1][j + 1] + (s[i] == t[j]), dp[i + 1][j],
                            dp[i][j + 1]});

    for (int i = 0, j = 0; i < n && j < m;) {
        if (s[i] == t[j] && dp[i + 1][j + 1] + 1 == dp[i][j]) {
            cout << s[i];
            ++i;
            ++j;
        } else if (dp[i + 1][j] == dp[i][j])
            ++i;
        else
            ++j;
    }
    cout << endl;

    return 0;
}
