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

const int INF = numeric_limits<int>::max();
const int NINF = numeric_limits<int>::min();
vvi adj;
vi d;
vi as;
vi ans;

void dfs(int v = 0, int p = -1) {
    int j = upper_bound(ALL(d), as[v]) - d.begin();
    ii changed{-1, -1};
    if (d[j - 1] < as[v] && as[v] < d[j]) {
        changed = mp(j, d[j]);
        d[j] = as[v];
    }
    if (~p) {
        if (d[j] < INF)
            ans[v] = max(j, ans[p]);
        else
            ans[v] = ans[p];
    } else {
        ans[v] = 1;
    }
    for (int u : adj[v])
        if (u != p) dfs(u, v);

    if (~changed.fi) {
        d[changed.fi] = changed.se;
    }
}
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;
    adj.assign(n, vi());
    as.assign(n, 0);
    d.assign(n + 1, INF);
    d[0] = NINF;
    ans.assign(n, -1);
    F0R (i, n)
        cin >> as[i];
    F0R (i, n - 1) {
        int a, b;
        cin >> a >> b;
        --a;
        --b;
        adj[a].pb(b);
        adj[b].pb(a);
    }
    dfs();

    for (int i : ans) {
        cout << i << endl;
    }

    return 0;
}