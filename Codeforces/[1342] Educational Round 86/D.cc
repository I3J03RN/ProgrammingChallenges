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
//#define endl '\n'
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

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, k;
    cin >> n >> k;
    vi cnt(k + 1);
    F0R (i, n) {
        int t;
        cin >> t;
        ++cnt[t];
    }
    vi cs(k + 1);
    FOR (i, 1, k + 1)
        cin >> cs[i];
    vvi out(n);
    vi s(n);
    for (int i = k; i > 0; --i) {
        int l = 0, r = n - 1;
        while (l < r) {
            int m = (l + r) / 2;
            if (s[m] >= cs[i]) {
                l = m + 1;
            } else
                r = m;
        }
        int cur = l;
        dout << dvar(cur) << endl;
        while (cnt[i]--) {
            while (SZ(out[cur]) == cs[i]) ++cur;
            out[cur].pb(i);
            ++s[cur];
        }
    }
    dout << dvar(out) << endl;
    while (out.back().empty()) out.pop_back();
    cout << SZ(out) << endl;
    for (auto& v : out)
        if (!v.empty()) {
            cout << SZ(v);
            for (int i : v) cout << ' ' << i;
            cout << endl;
        }

    return 0;
}
