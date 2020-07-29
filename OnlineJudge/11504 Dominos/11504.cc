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

vvi adj;
vi dfs_num, dfs_low, S;
vector<bool> onStack;
int dfsCounter;
void scc(int v, vvi& sccs) {
    dfs_num[v] = dfs_low[v] = dfsCounter++;
    S.push_back(v);
    onStack[v] = true;
    for (int u : adj[v]) {
        if (dfs_num[u] == -1) scc(u, sccs);
        if (onStack[u]) ckmin(dfs_low[v], dfs_low[u]);
    }
    if (dfs_num[v] == dfs_low[v]) {
        sccs.eb();
        int u;
        do {
            u = S.back();
            S.pop_back();
            onStack[u] = 0;
            sccs.back().pb(u);
        } while (u != v);
    }
}
vvi scc() {
    dfs_num.assign(SZ(adj), -1);
    dfs_low.assign(SZ(adj), 0);
    onStack.assign(SZ(adj), 0);
    dfsCounter = 0;
    vvi sccs;
    F0R (i, SZ(adj))
        if (!~dfs_num[i]) scc(i, sccs);
    return sccs;
}

void solve() {
    int n, mm;
    cin >> n >> mm;
    adj.assign(n, vi());
    while (mm--) {
	int a, b;
	cin >> a >> b;
	--a; --b;
	adj[a].pb(b);
    }
    vvi sccs = scc();
    dout << dvar(sccs) << endl;
    vi m(n);
    for (auto& v : sccs) {
	for (int u : v) {
	    m[u] = v.front();
	}
    }
    vi in(n);
    F0R (v, n) {
	for (int u : adj[v]) {
	    if (m[v] != m[u])
	        ++in[m[u]];
	}
    }

    int cnt = 0;
    F0R (i, n) {
        cnt += m[i] == i && in[i] == 0;
    }

    cout << cnt << endl;
    
    adj.clear();
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int tt;
    cin >> tt;
    FOR (t, 1, tt + 1) {
        // cout << "Case #" << t << ": ";
        solve();
    }

    return 0;
}
