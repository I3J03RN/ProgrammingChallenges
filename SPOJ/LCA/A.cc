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

struct LCA {
  vi height, eulerTour, first;
  vvi idx;
  LCA(vvi& adj, int root = 0)
      : height(SZ(adj), -1), first(SZ(adj), -1) {
    dfs(adj, root);
    build();
    dout << dvar(eulerTour) << endl;
    dout << dvar(height) << dvar(first) << endl;
    for (auto& v : idx) dout << dvar(v) << endl;
  }
  void build() {
    const int logn = ceil(log2l(SZ(eulerTour))) + 1;
    idx.assign(SZ(eulerTour), vi(logn));
    F0R (i, SZ(eulerTour))
      idx[i][0] = eulerTour[i];
    for (int j = 1; (1 << j) <= SZ(eulerTour); ++j)
      for (int i = 0; i + (1 << j) <= SZ(eulerTour); ++i) {
        int k = i + (1 << (j - 1));
        idx[i][j] = height[idx[i][j - 1]] < height[idx[k][j - 1]]
			? idx[i][j - 1] : idx[k][j - 1];
      }
  }
  int rmq(int l, int r) {
    int k = 31 - __builtin_clz(r - l + 1);
    return height[idx[l][k]] < height[idx[r - (1 << k) + 1][k]]
               ? idx[l][k] : idx[r - (1 << k) + 1][k];
  }
  void dfs(vvi& adj, int v = 0, int h = 0) {
    eulerTour.pb(v);
    first[v] = SZ(eulerTour) - 1;
    height[v] = h;
    for (int u : adj[v])
      if (first[u] == -1) {
        dfs(adj, u, h + 1);
        eulerTour.pb(v);
      }
  }
  int lca(int a, int b) {
    return rmq(min(first[a], first[b]), max(first[a], first[b]));
  }
};

void solve() {
    int n;
    cin >> n;
    vvi adj(n);
    vi in(n);
    F0R (i, n) {
	int cnt;
	cin >> cnt;
	while (cnt--) {
	    int b;
	    cin >> b;
	    --b;
	    adj[i].pb(b);
	    ++in[b];
	}
    }
    int root = 0;
    while (in[root]) ++root;
    LCA lca(adj, root);

    int q;
    cin >> q;
    while (q--) {
	int v, w;
	cin >> v >> w;
	--v; --w;
	cout << lca.lca(v, w) + 1<< endl;
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int tt;
    cin >> tt;
    FOR (t, 1, tt + 1) {
	cout << "Case " << t << ": " << endl;
	solve();
    }

    return 0;
}
