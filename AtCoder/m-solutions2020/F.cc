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

const int mxn = (int)5e5;

vi _d1[mxn], _d2[mxn];
vi _ve[mxn], _hz[mxn];
// \  this line is left here intentionally
vi* d1 = _d1;
// /
vi* d2 = _d2 + mxn / 2;
vi* ve = _ve + mxn / 2;
vi* hz = _hz + mxn / 2;

int main() {
  ios_base::sync_with_stdio(0);
  cout.tie(0); cin.tie(0);

  int n; cin >> n;
  vi xs(n), ys(n); vector<char> ts(n);
  F0R (i, n) cin >> xs[i] >> ys[i] >> ts[i];

  F0R (i, n) {
    d1[xs[i] + ys[i]].pb(i);
    d2[ys[i] - xs[i]].pb(i);
    if (ts[i] == 'D' || ts[i] == 'U') {
      ve[xs[i]].pb(i);
    } else {
      hz[ys[i]].pb(i);
    }
  }
  int best = (int)1e9;
  for (int d = 0; d <= 400000; ++d) {
    auto& v = d1[d];
    if (SZ(v) == 0) continue;
    sort(ALL(v), [&](int a, int b) { return xs[a] < xs[b]; });
    for (int i = 0, j = 0; i < SZ(v); ++i) {
      if (ts[v[i]] != 'R') continue;
      ckmax(j, i + 1);
      while (j < SZ(v) && ts[v[j]] != 'U') ++j;
      if (j < SZ(v)) {
        ckmin(best, (xs[v[j]] - xs[v[i]]) * 10);
      }
    }
    for (int i = 0, j = 0; i < SZ(v); ++i) {
      if (ts[v[i]] != 'D') continue;
      ckmax(j, i + 1);
      while (j < SZ(v) && ts[v[j]] != 'L') ++j;
      if (j < SZ(v)) {
        ckmin(best, (xs[v[j]] - xs[v[i]]) * 10);
      }
    }
  }
  for (int d = -200000; d <= 200000; ++d) {
    auto& v = d2[d];
    if (SZ(v) == 0) continue;
    sort(ALL(v), [&](int a, int b) { return xs[a] < xs[b]; });
    for (int i = 0, j = 0; i < SZ(v); ++i) {
      if (ts[v[i]] != 'U') continue;
      ckmax(j, i + 1);
      while (j < SZ(v) && ts[v[j]] != 'L') ++j;
      if (j < SZ(v)) {
        ckmin(best, (xs[v[j]] - xs[v[i]]) * 10);
      }
    }
    for (int i = 0, j = 0; i < SZ(v); ++i) {
      if (ts[v[i]] != 'R') continue;
      ckmax(j, i + 1);
      while (j < SZ(v) && ts[v[j]] != 'D') ++j;
      if (j < SZ(v)) {
        ckmin(best, (xs[v[j]] - xs[v[i]]) * 10);
      }
    }
  }

  for (int d = -200000; d <= 200000; ++d) {
    auto& v = ve[d];
    if (SZ(v) == 0) continue;
    sort(ALL(v), [&](int a, int b) { return ys[a] < ys[b]; });
    for (int i = 0, j = 0; i < SZ(v); ++i) {
      if (ts[v[i]] != 'U') continue;
      ckmax(j, i + 1);
      while (j < SZ(v) && ts[v[j]] != 'D') ++j;
      if (j < SZ(v)) {
        ckmin(best, (ys[v[j]] - ys[v[i]]) * 5);
      }
    }
  }
  for (int d = -200000; d <= 200000; ++d) {
    auto& v = hz[d];
    if (SZ(v) == 0) continue;
    sort(ALL(v), [&](int a, int b) { return xs[a] < xs[b]; });
    for (int i = 0, j = 0; i < SZ(v); ++i) {
      if (ts[v[i]] != 'R') continue;
      ckmax(j, i + 1);
      while (j < SZ(v) && ts[v[j]] != 'L') ++j;
      if (j < SZ(v)) {
        ckmin(best, (xs[v[j]] - xs[v[i]]) * 5);
      }
    }
  }
  if (best == (int)1e9) {
    cout << "SAFE" << endl;
  } else {
    cout << best << endl;
  }
  

  
  return 0;
}
