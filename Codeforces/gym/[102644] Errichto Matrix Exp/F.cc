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

const ll inf = (ll)3e18;

template<int sz, typename T>
struct matrix : public array<array<T, sz>, sz> {
  matrix() : array<array<T, sz>, sz>{} {}
  matrix(const T& val) : array<array<T, sz>, sz>{} {
    F0R (i, sz) (*this)[i][i] = val;
  }
  static matrix full(const T& val) {
    matrix res{};
    for (auto& v : res) fill(ALL(v), val);
    return res;
  }
  matrix& operator+=(const matrix& o) {
    F0R (r, sz) F0R (c, sz) (*this)[r][c] += o[r][c];
    return *this;
  }
  matrix& operator-=(const matrix& o) {
    F0R (r, sz) F0R (c, sz) (*this)[r][c] -= o[r][c];
    return *this;
  }
  matrix& operator*=(const matrix& o) {
    return *this = *this * o;
  }
  matrix& operator*=(T v) {
    F0R (r, sz) F0R (c, sz) (*this)[r][c] *= v;
    return *this;
  }
  friend matrix operator+(const matrix a, const matrix& b) {
    return a += b;
  }
  friend matrix operator-(const matrix a, const matrix& b) {
    return a -= b;
  }
  friend matrix operator*(const matrix& a, const matrix& b) {
    matrix res = matrix::full((ll)inf);
    F0R (r, sz) F0R (c, sz) F0R (k, sz) ckmin(res[r][c], a[r][k] + b[k][c]);
    return res;
  }
  friend matrix operator*(matrix a, T v) {
    return a *= v;
  }
  friend matrix operator*(T v, matrix a) {
    return a *= v;
  }
};

using mat = matrix<100, ll>;

int main() {
  ios_base::sync_with_stdio(0);
  cout.tie(0); cin.tie(0);

  int n, m, k; cin >> n >> m >> k;
  mat res = mat::full((ll)0);
  mat adj = mat::full((ll)inf);
  while (m--) {
    int a, b; ll c; cin >> a >> b >> c;
    adj[a - 1][b - 1] = c ;
  }
  for (; k; k >>= 1) {
    if (k & 1) res *= adj;
    adj *= adj;
  }
  ll mn = (ll)inf;
  for (auto& v : res) for (auto i : v) ckmin(mn, i);
  if (mn > (ll)1e18) {
    cout << "IMPOSSIBLE" << endl;
    return 0;
  }
  cout << mn << endl;
  
  return 0;
}
