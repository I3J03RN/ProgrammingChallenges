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

void solve() {
  int n, x, y; cin >> n >> x >> y;
  vi bs(n); F0R (i, n) cin >> bs[i];
  vvi pos(n + 2); F0R (i, n) pos[bs[i]].pb(i);
  int filler = -1;
  set<ii, greater<ii>> q;
  FOR (i, 1, n + 2) {
    if (SZ(pos[i])) {
      q.emplace(SZ(pos[i]), i);
    } else {
      filler = i;
    }
  }
  vi sol(n, filler);
  F0R (_, x) {
    auto [cnt, v] = *q.begin(); q.erase(q.begin());
    sol[pos[v].back()] = v; pos[v].pop_back();
    if (--cnt) q.emplace(cnt, v);
  }
  y -= x;
  set<ii, greater<ii>> q2;
  for (auto [cnt, v] : q) q2.emplace(cnt, -v);
  while (y--) {
    if (q.empty()) {
      cout << "NO" << endl;
      return;
    }
    auto [cnt, v] = *q.begin(); q.erase(q.begin());
    auto it = q2.begin(); 
    if (it->se == -v) advance(it, 1);
    if (it == q2.end()) {
      ++y; continue;
      return;
    }
    if (cnt - 1) q.emplace(cnt - 1, v);
    auto [cnt2, v2] = *it;
    q2.erase(it);
    if (cnt2 - 1) q2.emplace(cnt2 - 1, v2);
    sol[pos[-v2].back()] = v; pos[-v2].pop_back();
  }
  cout << "YES" << endl;
  for (int i : sol) {
    cout << i << ' ';
  }
  cout << endl;
}

int main() {
  ios_base::sync_with_stdio(0);
  cout.tie(0); cin.tie(0);

  int tt = 1;
  cin >> tt;
  FOR (t, 1, tt + 1) {
    // cout << "Case #" << t << ": ";
    solve();
  }
  
  return 0;
}
