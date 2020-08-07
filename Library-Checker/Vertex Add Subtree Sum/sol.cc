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
#define eb emplace_back
#define pb push_back
#define mp make_pair
#define mt make_tuple
#define SZ(x) (int)(x).size()
// #define endl '\n'
#define FOR(a, b, c) for (auto a = (b); (a) < (c); ++(a))
#define F0R(a, b) FOR (a, 0, (b))
#define CEIL(a, b) ((a) + (b)-1) / (b)
template <class T>
bool ckmin(T& a, const T& b) {
  return a > b ? a = b, true : false;
}
template <class T>
bool ckmax(T& a, const T& b) {
  return a < b ? a = b, true : false;
}
#ifndef DEBUG
#define DEBUG 0
#endif
#define dout \
  if (DEBUG) std::cerr
#define dvar(...) " [" << #__VA_ARGS__ ": " << mt(__VA_ARGS__) << "] "
template <typename T>
struct IsC {
  template <typename C>
  static char test(typename C::const_iterator*);
  template <typename C>
  static int test(...);
  static const bool value = sizeof(test<T>(0)) == sizeof(char);
};
template <>
struct IsC<string> {
  static const bool value = false;
};
template <typename C>
typename enable_if<IsC<C>::value, ostream&>::type operator<<(ostream&, const C&);
template <typename T1, typename T2>
ostream& operator<<(ostream&, const pair<T1, T2>&);
template <typename... T> using TS = tuple_size<tuple<T...>>;
template<size_t idx, typename... T>
typename enable_if<TS<T...>::value == idx + 1, ostream&>::type
operator<<(ostream& o, const tuple<T...>& t) {
  return o << ", " << get<idx>(t) << ')';
}
template<size_t idx, typename... T>
typename enable_if<0 < idx && idx + 1 < TS<T...>::value, ostream&>::type
operator<<(ostream& o, const tuple<T...>& t) {
  return operator<<<idx + 1>(o << ", " << get<idx>(t), t);
}
template<size_t idx = 0, typename... T>
typename enable_if<1 < TS<T...>::value && !idx, ostream&>::type
operator<<(ostream& o, const tuple<T...>& t) {
  return operator<<<idx + 1>(o << '(' << get<idx>(t), t);
}
template<typename T>
ostream& operator<<(ostream& o, const tuple<T>& t) {
  return o << get<0>(t);
}
template <typename T1, typename T2>
ostream& operator<<(ostream& o, const pair<T1, T2>& p) {
  return o << mt(p.fi, p.se);
}
template <typename C>
typename enable_if<IsC<C>::value, ostream&>::type operator<<(
    ostream& o, const C& c) {
  o << '[';
  for (auto it = c.cbegin(); it != c.cend(); ++it)
    o << *it << (next(it) != c.cend() ? ", " : "");
  return o << ']';
}
template <typename T>
void tprint(vector<vector<T>>& v, size_t width = 0, ostream& o = cerr) {
  if (!DEBUG) return;
  for (const auto& vv : v) {
    for (const auto& i : vv) o << setw(width) << i;
    o << endl;
  }
}

struct ST {
  using T = ll;
  const T unit = 0;
  T merge(T l, T r) { return l + r; };
  int n;
  vector<T> data;
  ST(int n) : n(n), data(2 * n) {}
  ST(vector<T>& v) : n(SZ(v)), data(2 * SZ(v)) {
    copy(ALL(v), data.begin() + SZ(v));
    build();
  }
  void build() {
    for (int i = n - 1; i; --i)
      data[i] = merge(data[i << 1], data[i << 1 | 1]);
  }
  T query(int l, int r) {
    T li = unit, ri = unit;
    for (l += n, r += n; l < r; r >>= 1, l >>= 1) {
      if (l & 1) li = merge(li, data[l++]);
      if (r & 1) ri = merge(data[--r], ri);
    }
    return merge(li, ri);
  }
  void update(int i, T val) {
    for (data[i += n] += val; i > 1; i >>= 1)
      data[i >> 1] = merge(data[i & ~1], data[i | 1]);
  }
};
struct HLD {
  int n;
  vi par, sz, height;
  vvi paths;
  vi in, pos;
  ST st;
  HLD(vvi& adj, vector<ST::T> val, int root = 0)
    : n{SZ(adj)}, par(n), sz(n, 1), height(n), in(n), pos(n), st{n} {
    dfssz(adj, root);
    vi order; 
    dfsbuild(adj, root, order);
    int j = 0;
    for (auto it = order.crbegin(); it != order.crend(); ++it)
      for (int v : paths[*it]) st.data[st.n + (pos[v] = j++)] = val[v];
    st.build();
  }
  void dfssz(vvi& adj, int v, int h = 0, int p = -1) {
    par[v] = p;
    height[v] = h;
    for (int u : adj[v]) {
      if (p != u) {
        dfssz(adj, u, h + 1, v);
        sz[v] += sz[u];
      }
    }
  }
  void dfsbuild(vvi& adj, int v, vi& order, int p = -1, bool heavy = false) {
    if (heavy) {
      paths[in[v] = in[p]].pb(v);
    } else {
      in[v] = SZ(paths);
      paths.pb({v});
    }
    int h = -1;
    for (int u : adj[v]) {
      if (p != u) {
        if (sz[u] > sz[v] / 2) h = u;
        else dfsbuild(adj, u, order, v);
      }
    }
    if (~h) dfsbuild(adj, h, order, v, true);
    if (paths[in[v]][0] == v) order.pb(in[v]);
  }
  void update(int v, ST::T val) { st.update(pos[v], val); }
  ST::T queryPath(int a, int b) {
    ST::T v = st.unit;
    while (in[a] != in[b]) {
      if (height[a] < height[b]) swap(a, b);
      if (in[a] == 0) swap(a, b);
      v = st.merge(v, st.query(pos[paths[in[a]][0]], pos[a] + 1));
      a = par[paths[in[a]][0]];
    }
    if (height[a] > height[b]) swap(a, b);
    return st.merge(v, st.query(pos[a], pos[b] + 1));
  }
  ST::T querySubtree(int v) {
    return st.query(pos[v], pos[v] + sz[v]);
  }
};


int main() {
  ios_base::sync_with_stdio(0);
  cout.tie(0); cin.tie(0);

  int n, q; cin >> n >> q;
  vector<ll> as(n); F0R (i, n) cin >> as[i];
  vvi adj(n);
  FOR (i, 1, n) {
    int p; cin >> p;
    adj[p].pb(i);
  }
  HLD hld(adj, as);
  while (q--) {
    int t; cin >> t;
    if (t) {
      int u; cin >> u;
      cout << hld.querySubtree(u) << endl;
    } else {
      int v; ll x; cin >> v >> x;
      hld.update(v, x);
    }
  }
  
  return 0;
}
