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
  using T = ll;
  const T unit = numeric_limits<T>::max();
  T merge(T l, T r) { return min(l, r); };
  int n;
  vector<T> data;
  ST(int n) : n(n), data(2 * n, unit) {}
  ST(vector<T>& v) : n(SZ(v)), data(2 * SZ(v)) {
    copy(ALL(v), data.begin() + SZ(v));
    build();
  }
  void build() {
    for (int i = n - 1; i; --i)
      data[i] = merge(data[i << 1], data[i << 1 | 1]);
  }
  void reset(int nn) {
    n = nn;
    data.clear();
    data.assign(2 * n, unit);
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

int n, m, a, b; 
vvi adj;
vector<ll> C;
ST all{0};
vi pos, lvl, fstlvl;
vector<ll> G;

void dfs(int v, int p, int base) {
  if (m >= lvl[v] - base) {
    G[v] = all.query(fstlvl[min(n - 1, 2 * base + m - lvl[v])], pos[v]);
  }
  if (G[v] < numeric_limits<ll>::max() && C[v]) {
    all.update(pos[v], G[v] + C[v]);
  }
  for (int u : adj[v]) {
    if (u != p) {
      dfs(u, v, base);
    }
  } 
}

void solve() {
  cin >> n >> m >> a >> b;
  --a; --b;
  adj.assign(n, vi());
  C.assign(n, 0);
  all.reset(n);
  pos.assign(n, 0);
  lvl.assign(n, 0);
  fstlvl.assign(n, n);
  G.assign(n, numeric_limits<ll>::max());
  F0R (i, n) {
    int p; cin >> p >> C[i]; --p;
    if (~p) {
      adj[p].pb(i);
      adj[i].pb(p);
    }
  }
  vi p(n, -1);
  vvi level(n);
  queue<ii> q;
  q.emplace(b, 0);
  p[b] = b;
  while (SZ(q)) {
    auto [v, l] = q.front(); q.pop();
    level[l].pb(v);
    for (int u : adj[v]) {
      if (p[u] == -1) {
        p[u] = v;
        q.emplace(u, l + 1);
      }
    }
  }
  for (int i = 0, j = n - 1; i < n; ++i) {
    for (int v : level[i]) {
      ckmin(fstlvl[i], j);
      pos[v] = j--;
      lvl[v] = i;
    }
  }
  F0R (i, n) {
    if (fstlvl[i] == n) fstlvl[i] = 0;
  }
  // dout << endl << dvar(fstlvl) << endl << dvar(pos) << endl << dvar(lvl) << endl;
  all.update(pos[a], 0);
  for (int cur = a, idx = 1; cur != p[cur]; ++idx) {
    int prev = cur;
    cur = p[cur];
    for (int u : adj[cur]) {
      if (prev != u && p[cur] != u) {
        dfs(u, cur, lvl[cur]);
      }
    }
    // dout << dvar(cur, fstlvl[min(n - 1, lvl[cur] + m)], pos[cur]) << endl;
    G[cur] = all.query(fstlvl[min(n - 1, lvl[cur] + m)], pos[cur]);
    if (G[cur] < numeric_limits<ll>::max() && C[cur]) {
      all.update(pos[cur], G[cur] + C[cur]);
    }
  }

  cout << (G[b] == numeric_limits<ll>::max() ? -1 : G[b]) << endl;
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);

  int tt;
  cin >> tt;
  FOR (t, 1, tt + 1) {
    cerr << t << endl;
    cerr.flush();
    cout << "Case #" << t << ": ";
    solve();
  }
}
