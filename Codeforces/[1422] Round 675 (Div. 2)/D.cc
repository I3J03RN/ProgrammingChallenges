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
#define eb emplace_back
#define pb push_back
#define mp make_pair
#define mt make_tuple
#define endl '\n'
#define ALL(x) (x).begin(), (x).end()
#define RALL(x) (x).rbegin(), (x).rend()
#define SZ(x) (int)(x).size()
#define FOR(a, b, c) for (auto a = (b); (a) < (c); ++(a))
#define F0R(a, b) FOR (a, 0, (b))
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
#define dout if (DEBUG) cerr
#define dvar(...) " \x1b[35m[" << #__VA_ARGS__ ": " << mt(__VA_ARGS__) << "]\x1b[0m "
template <typename T>
true_type const_iterator_check(typename T::const_iterator*);
template <typename T>
false_type const_iterator_check(...);
template <typename T>
struct IsC : decltype(const_iterator_check<T>(nullptr)) {};
template <>
struct IsC<string> : false_type {};
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

int main() {
  ios_base::sync_with_stdio(0);
  cout.tie(0); cin.tie(0);

  int n, m; cin >> n >> m; 
  int sx, sy, fx, fy; cin >> sx >> sy >> fx >> fy;
  vii ms(m); F0R (i, m) cin >> ms[i].fi >> ms[i].se;
  set<ii> xs, ys;
  F0R (i, m) {
    xs.emplace(ms[i].fi, i);
    ys.emplace(ms[i].se, i);
  }
  vector<vector<pair<int, ll>>> adj(m + 1);
  F0R (i, m) {
    auto it = xs.find(mp(ms[i].fi, i));
    auto it2 = next(it);
    if (it2 != xs.end()) adj[i].eb(it2->se, min(abs(ms[i].fi - ms[it2->se].fi), abs(ms[i].se - ms[it2->se].se)));
    if (it != xs.begin()) {
      auto it3 = prev(it);
      adj[i].eb(it3->se, min(abs(ms[i].fi - ms[it3->se].fi), abs(ms[i].se - ms[it3->se].se)));
    }
    it = ys.find(mp(ms[i].se, i));
    it2 = next(it);
    if (it2 != ys.end()) adj[i].eb(it2->se, min(abs(ms[i].fi - ms[it2->se].fi), abs(ms[i].se - ms[it2->se].se)));
    if (it != ys.begin()) {
      auto it3 = prev(it);
      adj[i].eb(it3->se, min(abs(ms[i].fi - ms[it3->se].fi), abs(ms[i].se - ms[it3->se].se)));
    }
  }
  vector<ll> dist(m);
  set<pair<ll, int>> q;
  F0R (i, m) {
    q.emplace(dist[i] = abs(fx - ms[i].fi) + abs(fy - ms[i].se), i);
  }
  while (!q.empty()) {
    auto [d, v] = *q.begin(); q.erase(q.begin());
    if (dist[v] < d) continue;
    for (auto [u, du] : adj[v])
      if (ckmin(dist[u], d + du)) q.emplace(d + du, u);
  }

  ll best = abs(fx - sx) + abs(fy - sy);
  F0R (i, m) {
    ckmin(best, dist[i] + min(abs(sx - ms[i].fi), abs(sy - ms[i].se)));
  }

  cout << best << endl;

  
  return 0;
}
