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

struct LCA {
  int timer = 0, logN, root;
  vi tin, tout;
  vvi up, weight;
  LCA(vvii& adj, int root = 0)
      : logN(31 - __builtin_clz(SZ(adj))), root(root),
        tin(SZ(adj)), tout(SZ(adj)),
        up(SZ(adj), vi(logN + 1, root)),
        weight(SZ(adj), vi(logN + 1, root)) {
    lcadfs(adj, root);
  }
  void lcadfs(vvii& adj, int v, int p = -1,
              int w = numeric_limits<int>::max()) {
    tin[v] = ++timer;
    up[v][0] = ~p ? p : root;
    weight[v][0] = w;
    FOR (i, 1, logN + 1) {
      up[v][i] = up[up[v][i - 1]][i - 1];
      weight[v][i] =
          min(weight[v][i - 1], weight[up[v][i - 1]][i - 1]);
    }
    for (auto [u, w] : adj[v])
      if (u != p) lcadfs(adj, u, v, w);
    tout[v] = ++timer;
  }
  bool isAnc(int v, int u) {
    return tin[v] <= tin[u] && tout[v] >= tout[u];
  }
  int lca(int v, int u) {
    if (isAnc(v, u)) return v;
    if (isAnc(u, v)) return u;
    for (int l = logN; ~l; --l)
      if (!isAnc(up[v][l], u)) v = up[v][l];
    return up[v][0];
  }
  // returns max weight of an edge on the the path v -- u
  int maxPath(int v, int u) {
    int anc = lca(v, u);
    return min(maxPathAnc(v, anc), maxPathAnc(u, anc));
  }
  // returns max weight of an edge on path from v to u (isAnc(u, v))
  int maxPathAnc(int v, int u) {
    int res = numeric_limits<int>::max();
    for (int l = logN; ~l; --l)
      if (isAnc(u, up[v][l])) {
        ckmin(res, weight[v][l]);
        v = up[v][l];
      }
    return res;
  }
};


int main() {
  ios_base::sync_with_stdio(0);
  cout.tie(0); cin.tie(0);

  int n, m; cin >> n >> m;
  assert(m + 1 == n);
  vvii adj(n);
  F0R (_, m) {
    int a, b, w; cin >> a >> b >> w; --a; --b;
    adj[a].eb(b, w); adj[b].eb(a, w);
  }
  LCA lca(adj);
  int q; cin >> q;
  while (q--) {
    int a, b; cin >> a >> b;
    cout << lca.maxPath(a - 1, b - 1) << endl;
  }
  
  return 0;
}
