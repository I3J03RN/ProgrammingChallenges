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

struct edge {
    int u, v, w, idx;
};

struct DSU {
    DSU(int size) : msize(size), data(size, -1) {}
    bool sameSet(int a, int b) { return find(a) == find(b); }
    int find(int x) { return data[x] < 0 ? x : data[x] = find(data[x]); }
    bool join(int a, int b) {
        a = find(a), b = find(b);
        if (a == b) return false;
        if (data[a] > data[b]) swap(a, b);
        data[a] += data[b], data[b] = a;
        return --msize, true;
    }
    int size() { return msize; }
    int size(int a) { return -data[find(a)]; }
    int msize;
    vi data;
};

struct LCA {
    int timer = 0, logN, root;
    vi tin, tout;
    vvi up, weight;
    LCA(vvii& adj, int root = 0)
        : logN(31 - __builtin_clz(SZ(adj))),
          root(root),
          tin(SZ(adj)),
          tout(SZ(adj)),
          up(SZ(adj), vi(logN + 1, root)),
          weight(SZ(adj), vi(logN + 1, root)) {
        lcadfs(adj, root);
    }
    void lcadfs(vvii& adj, int v, int p = -1, int w = numeric_limits<int>::min()) {
        tin[v] = ++timer;
        up[v][0] = ~p ? p : root;
        weight[v][0] = w;
        FOR (i, 1, logN + 1) {
            up[v][i] = up[up[v][i - 1]][i - 1];
            weight[v][i] = max(weight[v][i - 1], weight[up[v][i - 1]][i - 1]);
        }
        for (auto [u, w] : adj[v])
            if (u != p) lcadfs(adj, u, v, w);
        tout[v] = ++timer;
    }
    bool isAnc(int v, int u) { return tin[v] <= tin[u] && tout[v] >= tout[u]; }
    int lca(int v, int u) {
        if (isAnc(v, u)) return v;
        if (isAnc(u, v)) return u;
        R0F (l, logN)
            if (!isAnc(up[v][l], u)) v = up[v][l];
        return up[v][0];
    }
    // returns max weight of an edge on the the path v -- u
    int maxPath(int v, int u) {
        int anc = lca(v, u);
        return max(maxAnc(v, anc), maxAnc(u, anc));
    }
    // invariant: isAnc(u, v)
    int maxAnc(int v, int u) {
        int res = numeric_limits<int>::min();
        R0F (l, logN)
            if (isAnc(u, up[v][l])) {
                ckmax(res, weight[v][l]);
                v = up[v][l];
            }
        return res;
    }
};

vector<edge> edges;
vvii adj;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, m;
    cin >> n >> m;
    edges.resize(m);
    adj.resize(n);
    F0R (i, m) {
        auto& e = edges[i];
        cin >> e.v >> e.u >> e.w;
        --e.v;
        --e.u;
        e.idx = i;
    }
    sort(ALL(edges), [](edge& a, edge& b) { return a.w < b.w; });

    DSU dsu(n);
    ll w = 0;
    F0R (i, m) {
        if (SZ(dsu) == 1) break;
        auto& e = edges[i];
        if (dsu.join(e.v, e.u)) {
            w += e.w;
            adj[e.v].eb(e.u, e.w);
            adj[e.u].eb(e.v, e.w);
        }
    }
    LCA lca(adj);
    vector<ll> ans(m);
    F0R (i, m) {
        auto& e = edges[i];
        if (lca.up[e.v][0] == e.u || lca.up[e.u][0] == e.v) {
            ans[e.idx] = w;
        } else {
            ans[e.idx] = w - lca.maxPath(e.v, e.u) + e.w;
        }
    }
    for (ll i : ans) cout << i << endl;

    return 0;
}
