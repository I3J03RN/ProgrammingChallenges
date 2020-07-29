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


struct ST {
  int n, nn;
  vi value;
  int inline left(int p) { return p << 1; }
  int inline right(int p) { return (p << 1) + 1; }
  int build(const vi& a, int p, int h, int L, int R) {
    if (L == R) {
      return value[p] = a[L];
    } else {
      if (h & 1) {
        return value[p] = build(a, left(p), h - 1, L, (R + L) / 2)
          | build(a, right(p), h - 1, (R + L) / 2 + 1, R);
      }
      return value[p] = build(a, left(p), h - 1, L, (R + L) / 2)
        ^ build(a, right(p), h - 1, (R + L) / 2 + 1, R);
    }
  }
  // int q(int p, int L, int R, int i, int j) {
  //   if (i > R || j < L) return numeric_limits<int>::min();
  //   if (i <= L && R <= j) return value[p];
  //   return max(rmq(left(p), L, (L + R) / 2, i, j),
  //              rmq(right(p), (L + R) / 2 + 1, R, i, j));
  // }
  int u(int p, int L, int R, int h, int i, int val) {
    if (i > R || i < L) return value[p];
    if (L == R) return value[p] = val;
    if (h & 1) {
      return value[p] = u(left(p), L, (L + R) / 2, h - 1, i, val)
        | u(right(p), (L + R) / 2 + 1, R, h - 1, i, val);
    }
    return value[p] = u(left(p), L, (L + R) / 2, h - 1, i, val)
      ^ u(right(p), (L + R) / 2 + 1, R, h - 1, i, val);
  }
  ST(const vi& a, int nn) : n(SZ(a)), nn(nn), value(SZ(a) * 4){
    build(a, 1, nn, 0, SZ(a) - 1);
  }
  int q() { return value[1]; }
  void u(int i, int val) { u(1, 0, n - 1, nn, i, val); }
  int size() { return n; }
};


void solve() {
  int n, m;
  cin >> n >> m;
  vi as(1 << n);
  F0R (i, 1 << n) cin >> as[i];
  ST st(as, n);
  while (m--) {
    int p, b;
    cin >> p >> b;
    st.u(p - 1, b);
    cout << st.q() << endl;
  }
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
