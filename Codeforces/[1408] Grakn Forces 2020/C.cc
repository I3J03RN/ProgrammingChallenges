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
#define dvar(...) " [" << #__VA_ARGS__ ": " << mt(__VA_ARGS__) << "] "
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

constexpr double eps = 1e-9;

void solve() {
  int n; int l; cin >> n >> l;
  vi as(n); F0R (i, n) cin >> as[i];
  vector<double> rs(n + 2), re(n + 2);
  rs[0] = 0; re[n + 1] = 0;
  int last = 0;
  F0R (i, n) {
    rs[i + 1] = rs[i] + (as[i] - last) / (double) (i + 1);
    last = as[i];
  }
  rs[n + 1] = rs[n] + (l - as[n - 1]) / (double) n;
  last = l;
  F0R (i, n) {
    re[n - i] = re[n + 1 - i] + (last - as[n - 1 - i]) / (double) (i + 1);
    last = as[n - 1 - i];
  }
  re[0] = re[1] + as[0] / (double) n;
  dout << dvar(rs) << endl << dvar(re) << endl;
  F0R (i, n + 2) {
    if (abs(rs[i] - re[i]) < eps) {
      cout << rs[i] << endl;
      return;
    }
  }
  F0R (i, n + 1) {
    if (rs[i] <= re[i] && rs[i + 1] >= re[i + 1]) {
      dout << dvar(i) << endl;
      double ps = 0;
      if (i > 0) {
        ps = as[i - 1];
      }
      double pe = l;
      if (i < n) {
        pe = as[i];
      }
      double vs = i + 1;
      double ve = n + 1 - i;
      dout << dvar(ps, vs, pe, ve) << endl;
      if (rs[i] < re[i + 1]) {
        ps += vs * (re[i + 1] - rs[i]);
      } else {
        pe -= ve * (rs[i] - re[i + 1]);
      }
      dout << dvar(ps, vs, pe, ve) << endl;
      cout << setprecision(12) << fixed << max(rs[i], re[i + 1]) + ((pe - ps) / (vs + ve)) << endl;
      
    }
  }
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
