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
#define endl '\n'
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
  using T = int;
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
    for (data[i += n] = val; i > 1; i >>= 1)
      data[i >> 1] = merge(data[i & ~1], data[i | 1]);
  }
};

struct LCA {
  vi height, eulerTour, first, last, par;
  vvi idx;
  LCA(vvi& adj, int root = 0)
    : height(SZ(adj), -1), first(SZ(adj), -1), last(SZ(adj), -1), par(SZ(adj), -1) {
    dfs(adj, root);
    build();
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
        par[u] = v;
        dfs(adj, u, h + 1);
        eulerTour.pb(v);
      }
    last[v] = SZ(eulerTour);
  }
  int lca(int a, int b) {
    return rmq(min(first[a], first[b]), max(first[a], first[b]));
  }
};


int main() {
  ios_base::sync_with_stdio(0);
  cout.tie(0); cin.tie(0);

  int n, m; cin >> n >> m;
  vvi adj(n + 1);
  F0R (_, n - 1) {
    int a, b; cin >> a >> b;
    adj[a].pb(b); adj[b].pb(a);
  }
  LCA lca(adj, 1);
  auto &first = lca.first, &last = lca.last, &par = lca.par;
  ST st(SZ(lca.eulerTour));
  while (m--) {
    int a, b; cin >> a >> b;
    ++st.data[first[a] + st.n]; ++st.data[st.n + first[b]];
    int l = lca.lca(a, b);
    --st.data[st.n + first[l]];
    if (~par[l]) {
      --st.data[st.n + first[par[l]]];
    }
  }
  st.build();
  FOR (i, 1, n + 1) {
    cout << st.query(first[i], last[i]) << ' ';
  }
  cout << endl;
  
  return 0;
}
