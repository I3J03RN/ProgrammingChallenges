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
array<int, 4> dr{0, 0, 1, -1}, dc{1, -1, 0, 0};
array<char, 4> g{'L', 'R', 'U', 'D'};
int n, m; 
vector<string> f;
bool ok(int r, int c) {
  return 0 <= min(r, c) && r < n && c < m && (f[r][c] == '.' || f[r][c] == 'A');
}
vector<vector<char>> go;


int main() {
  ios_base::sync_with_stdio(0);
  cout.tie(0);

  cin >> n >> m;
  f.assign(n, "");
  go.assign(n, vector<char>(m, '?'));
  for (auto& s : f) cin >> s;
  queue<ii> q;
  F0R (r, n) F0R (c, m) if (f[r][c] == 'B') {q.emplace(r, c); f[r][c] = '#';}
  int er, ec;
  F0R (r, n) F0R (c, m) if (f[r][c] == 'A') {er = r; ec = c;}
  
  while (SZ(q)) {
    auto [r, c] = q.front(); q.pop();   
    F0R (i, 4) {
      int rr = r + dr[i], cc = c + dc[i];
      if (ok(rr, cc)) {
        go[rr][cc] = g[i];
        f[rr][cc] = '#';
        q.emplace(rr, cc);
      }
    }
  }
  tprint(go);
  if (go[er][ec] == '?') {
    cout << "NO" << endl;
    return 0;
  }
  int r = er, c = ec;
  string out;
  while (go[r][c] != '?') {
    out.pb(go[r][c]);
    if (go[r][c] == 'U') --r;
    else if (go[r][c] == 'D') ++r;
    else if (go[r][c] == 'R') ++c;
    else --c;
  }
  cout << "YES" << endl << SZ(out) << endl << out << endl;





  return 0;
}
