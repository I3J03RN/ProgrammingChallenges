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

int main() {
  ios_base::sync_with_stdio(0);
  cout.tie(0); cin.tie(0);

  int n; cin >> n;
  vi as(n), bs(n);
  F0R (i, n) cin >> as[i];
  F0R (i, n) cin >> bs[i];
  vi cnt(n + 1);
  for (int i : bs) ++cnt[i];
  vi cnta(n + 1);
  for (int i : as) ++cnta[i];

  vi start(n + 1, n + 1), res(n);
  F0R (i, n) ckmin(start[as[i]], i);
  as.erase(unique(ALL(as)), as.end());
  // cnt in bs, remaining, val 
  priority_queue<tuple<int, int, int>> q;
  for (int i : as) {
    q.emplace(cnt[i], cnta[i], -i);
  }
  // cnt in bs, v
  priority_queue<ii> q2;
  for (int i : bs) {
    q2.emplace(cnt[i], i);
  }
  dout << dvar(cnt, cnta, as, res, start) << endl;
  while (!q2.empty()) {
    auto [c, v] = q2.top(); q2.pop();
    dout << dvar(c, v) << endl;
    vector<tuple<int, int, int>> t;
    if (!q.empty() && -get<2>(q.top()) == v) {
      t.pb(q.top()); q.pop();
    }
    if (q.empty()) {
      cout << "No" << endl;
      return 0;
    }
    auto [cc, r, vv] = q.top(); q.pop();
    dout << dvar(cc, r, vv) << endl; 
    res[start[-vv]++] = v;
    if (r - 1 > 0) {
      q.emplace(cc, r - 1, vv);
    }
    if (!t.empty()) {
      q.push(t.front());
    }
  }
  

  cout << "Yes" << endl;
  for (int i : res) cout << i << ' ';
  cout << endl;
  
  return 0;
}
