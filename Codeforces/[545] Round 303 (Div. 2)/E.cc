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

vvii adj;
vector<ll> weight;

const ll inf = 1e18;
vi dijkstra(int start) {
  vector<ll> dist(SZ(adj), inf);
  vi p(SZ(adj), -1);
  set<pair<ll,int>> q;
  q.emplace(0, start);
  dist[start] = 0;
  p[start] = -1;
  while (!q.empty()) {
    auto [d, v] = *q.begin(); q.erase(q.begin());
    if (dist[v] < d) continue;
    for (auto [u, i] : adj[v]) {
      ll du = weight[i];
      if (ckmin(dist[u], d + du)) {
        q.emplace(d + du, u);
        p[u] = i;
      } else if (dist[u] == d + du && weight[i] < weight[p[u]]) {
        p[u] = i;
      }
    }
  }
  return p;
}

void solve() {
  int n, m;
  cin >> n >> m;
  adj.resize(n);
  weight.resize(m);
  F0R (i, m) {
    int u, v;
    cin >> u >> v >> weight[i];
    --u; --v;
    adj[u].eb(v, i);
    adj[v].eb(u, i);
  }

  int start;
  cin >> start;
  --start;
  vi p = dijkstra(start);
  dout << dvar(p) << endl;
  ll ans = 0;
  for (int i : p) {
    if (~i) ans += weight[i];
  }
  cout << ans << endl;
  for (int i : p) if (~i) cout << i + 1 << ' ';
  cout << endl;
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
