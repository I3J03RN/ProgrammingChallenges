#include <bits/stdc++.h>
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

void solve() {
    int n, m;
    cin >> n >> m;
    vi has(n, 1);
    vi wants(n);
    vvi adj(n);
    F0R (_, m) {
        int a, b;
        cin >> a >> b;
        --a;
        --b;
        adj[a].pb(b);
        adj[b].pb(a);
    }
    F0R (i, n)
        cin >> wants[i];

    vi is(n);
    iota(ALL(is), 0);
    sort(ALL(is), [&](int a, int b) { return wants[a] < wants[b]; });
    for (int i : is) {
        if (has[i] != wants[i]) {
            cout << -1 << endl;
            return;
        }
        for (int u : adj[i]) {
            if (wants[u] >= has[i]) {
                if (has[u] < has[i]) {
                    cout << -1 << endl;
                    return;
                }
                has[u] = has[i] + 1;
            }
        }
    }
    for (int i : is) cout << i + 1 << ' ';
    cout << endl;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int tt = 1;
    FOR (t, 1, tt + 1) {
        // cout << "Case #" << t << ": ";
        solve();
    }

    return 0;
}
