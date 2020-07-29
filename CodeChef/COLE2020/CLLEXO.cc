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
array<int, 2> dr{0, 1}, dc{1, 0};

void solve() {
  int n, m; cin >> n >> m;
  vector<string> ss(n);
  F0R (i, n) cin >> ss[i];
  vector<vector<bool>> valid(n + 1, vector<bool>(m + 1));
  valid[n - 1][m] = 1;
  for (int r = n - 1; r >= 0; --r) {
    for (int c = m - 1; c >= 0; --c) {
      if (ss[r][c] != '#')
        valid[r][c] = valid[r + 1][c] || valid[r][c + 1];
    }
  }
  // 0: unvisited, 1: left, 2: up
  vector<vector<int>> p(n, vector<int>(m));
  p[0][0] = -1;
  using T = tuple<int, char, int, int>;
  set<T> q;
  q.emplace(0, ss[0][0], 0, 0);
  vector<char> lvlmn(n + m, 127);
  while (SZ(q)) {
    dout << dvar(q) << endl;
    auto [lvl, cr, r, c] = *q.begin(); q.erase(q.begin());
    if (cr > lvlmn[lvl]) continue;
    lvlmn[lvl] = cr;
    F0R (i, 2) {
      int rr = r + dr[i], cc = c + dc[i];
      if (rr < n && cc < m && valid[rr][cc] && !p[rr][cc]) {
        p[rr][cc] = i + 1;
        q.emplace(lvl + 1, ss[rr][cc], rr, cc);
      }
    }
  }
  string out(n + m - 1, ss[0][0]);
  int r = n - 1, c = m - 1, i = m + n - 2;
  while (max(r, c) > 0) {
    out[i--] = ss[r][c];
    if (p[r][c] == 1) {
      --c;
    } else {
      --r;
    }
  }
  cout << out << endl;
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
