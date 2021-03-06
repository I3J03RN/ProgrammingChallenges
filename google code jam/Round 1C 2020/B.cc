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
int calc(ll a) {
    while (a >= 10) a /= 10;
    return a;
}
int len(ll a) {
    int n = 0;
    while (a) {
        ++n;
        a /= 10;
    }
    return n;
}
void solve() {
    int u;
    cin >> u;
    vector<pair<ll, string>> in(1e4);
    F0R (i, 1e4)
        cin >> in[i].fi >> in[i].se;
    set<char> chars;
    F0R (i, 1e4)
        for (char c : in[i].se) chars.insert(c);
    set<char> neverinfirst = chars;
    dout << dvar(chars) << endl;
    F0R (i, 1e4)
        neverinfirst.erase(in[i].se.ft);
    assert(SZ(neverinfirst) == 1);
    dout << dvar(neverinfirst) << endl;
    map<char, int> cmax;
    for (char c : chars) cmax[c] = 9;
    cmax[*neverinfirst.begin()] = 0;
    F0R (i, 1e4)
        if (len(in[i].fi) == SZ(in[i].se))
            cmax[in[i].se.ft] = min(cmax[in[i].se.ft], calc(in[i].fi));
    dout << dvar(cmax) << endl;
    F0R (i, 10) {
        for (auto it : cmax) {
            if (it.second == i) {
                cout << it.fi;
                break;
            }
        }
    }
    cout << endl;
}
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int tt;
    cin >> tt;
    FOR (t, 1, tt + 1) {
        cout << "Case #" << t << ": ";
        solve();
    }

    return 0;
}
