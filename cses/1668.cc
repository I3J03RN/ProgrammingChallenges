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
  for (auto& vv : v) {
    for (auto& i : vv) o << setw(width) << i;
    o << endl;
  }
}

template<bool D = false, typename L = bool>
struct G : vector<L> {
  int n;
  vvi adj;
  vector<bool> seen;
  G(int n, const L& l = L()) : vector<L>(n, l), n(n), adj(n) {}
  void add(int a, int b) {
    adj[a].pb(b);
    if (D) adj[b].pb(a);
  }
  void reset_seen() {
    seen.assign(n, false);
  }
  template<typename F>
  void dfs(int v, F visit, int p = -1) {
    seen[v] = true;
    visit(v, p);
    for (int u : adj[v]) {
      if (!seen[u]) {
        dfs(u, visit, v);
      }
    }
  }
  template<typename F, typename G>
  void dfs(int v, F visit, G peek, int p = -1) {
    seen[v] = true;
    visit(v, p);
    for (int u : adj[v]) {
      peek(u, v);
      if (!seen[u]) {
        dfs(u, visit, v);
      }
    }
  }
  template<typename F>
  void bfs(const vi& start, F visit, bool reset = true) {
    if (reset) reset_seen();
    queue<ii> q;
    for (int i : start) {
      seen[i] = true;
      q.emplace(i, -1);
    }
    while (!q.empty()) {
      int v, p;
      tie(v, p) = q.front(); q.pop();
      visit(v, p);
      for (int u : adj[v]) {
        if (!seen[u]) {
          seen[u] = true;
          q.emplace(u, v);
        }
      }
    }
  }
};


// vi color;
// vvi adj;

// bool dfs(int v = 0) {
//   for (int u : adj[v]) {
//     if (-1 == color[u]) {
//       color[u] = !color[v];
//       if (!dfs(u)) return 0;
//     } else if (color[u] == color[v]) {
//       return 0;
//     }
//   }

//   return 1;
// }

void solve() {
  int n, m;
  cin >> n >> m;
  // color.resize(n, -1); adj.resize(n);
  // while (m--) {
  //   int a, b;
  //   cin >> a >> b;
  //   --a; --b;
  //   adj[a].pb(b); adj[b].pb(a);
  // }
  // F0R (i, n) {
  //   if (-1 == color[i]) {
  //     color[i] = 0;
  //     if (!dfs(i)) {
  //       cout << "IMPOSSIBLE" << endl;
  //       return;
  //     }
  //   }
  // }
  // for (int i : color) cout << i + 1 << ' ';
  // cout << endl;

  G<true, int> g(n, -1);
  F0R (_, m) {
    int a, b; cin >> a >> b;
    g.add(a - 1, b - 1);
  }
  g.reset_seen();
  F0R (i, n) {
    if (!g.seen[i]) {
      g.dfs(i, [&](int v, int p) {
        g[v] = p == -1 ? 0 : !g[p];
      }, [&](int v, int p) {
        if (g[v] == g[p]) g[p] = -1;
      });
    }
  }
  if (count(ALL(g), -1)) {
    cout << "IMPOSSIBLE" << endl;
  } {
    for (int i : g) cout << i + 1 << ' ';
    cout << endl;
  }
}

int main() {
  ios_base::sync_with_stdio(0);
  cout.tie(0);

  int tt = 1;
  FOR (t, 1, tt + 1) {
    // cout << "Case #" << t << ": ";
    solve();
  }
  
  return 0;
}
