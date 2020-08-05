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

vi sz;
vector<ll> val;
vvi adj;
vi par;
vector<bool> heavy;
vi stidx, pos, stsz;
vi first;

void dfssz(int v = 1, int p = -1) {
  par[v] = p;
  for (int u : adj[v]) {
    if (p != u) {
      dfssz(u, v);
      sz[v] += sz[u];
    }
  }
}

void dfs(int v = 1, int p = -1) {
  for (int u : adj[v]) {
    if (p != u) {
      dfs(u, v);
      if (sz[u] > sz[v] / 2) {
        heavy[u] = true;
      }
    }
  } 
}

void dfsBuild(int v = 1, int p = -1) {
  if (heavy[v]) {
    stidx[v] = stidx[p];
    ++stsz[stidx[v]];
    pos[v] = pos[p] + 1;
  } else {
    stidx[v] = SZ(stsz);
    stsz.pb(1); first.pb(v);
    pos[v] = 0;
    
  }
  for (int u : adj[v]) {
    if (p != u) {
      dfsBuild(u, v);
    }
  }
}

int main() {
  ios_base::sync_with_stdio(0);
  cout.tie(0); cin.tie(0);

  int n, q; cin >> n >> q;
  sz.resize(n + 1, 1);
  adj.resize(n + 1);
  val.resize(n + 1);
  par.resize(n + 1);
  heavy.resize(n + 1);
  stidx.resize(n + 1, -1);
  pos.resize(n + 1, -1);
  FOR (i, 1, n + 1) {
    cin >> val[i];
  }
  F0R (_, n - 1) {
    int a, b; cin >> a >> b;
    adj[a].pb(b); adj[b].pb(a);
  }
  dfssz();
  dfs();
  dfsBuild();
  vector<ST> segs;
  for (int i : stsz) {
    segs.eb(i);
  }
  FOR (i, 1, n + 1) {
    segs[stidx[i]].data[segs[stidx[i]].n + pos[i]] = val[i];
  }
  for (auto& s : segs) s.build();
  dout << dvar(sz, par, heavy) << endl;
  dout << dvar(stidx, pos, stsz, first) << endl;

  while (q--) {
    int t; cin >> t;
    if (t == 1) {
      int x; ll k; cin >> x >> k;
      segs[stidx[x]].update(pos[x], k);
    } else {
      int x; cin >> x;
      ll sum = 0;
      while (~x) {
        sum += segs[stidx[x]].query(0, pos[x] + 1);
        x = par[first[stidx[x]]];
      }
      cout << sum << endl;
    }
  }
  
  return 0;
}
