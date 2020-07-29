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

struct mod {
  static const ll p = 1e9 + 7;
  ll val;
  mod() : val(0) {}
  mod(ll val) : val(val % p) { if (this->val < 0) this->val += p; }
  mod& operator+=(const mod& o) {
    val = (val + o.val) % p;
    return *this;
  }
  mod& operator-=(const mod& o) {
    val = (val - o.val + p) % p;
    return *this;
  }
  mod& operator*=(const mod& o) {
    val = val * o.val % p;
    return *this;
  }
  mod& operator/=(mod o) { return (*this) *= pow(o, p - 2); }
  mod& operator++() { return (*this) += 1; }
  mod operator++(int) { return ++(*this) - 1; }
  mod& operator--() { return (*this) -= 1; }
  mod operator--(int) { return --(*this) + 1; }
  mod friend operator+(mod a, const mod& b) { return a += b; }
  mod friend operator-(mod a, const mod& b) { return a -= b; }
  mod friend operator*(mod a, const mod& b) { return a *= b; }
  mod friend operator/(mod a, const mod& b) { return a /= b; }
  static mod pow(mod a, mod b) {
    mod res = 1;
    for (; b.val; b.val >>= 1, a = a * a)
      if (b.val & 1) res = res * a;
    return res;
  }
  friend istream& operator>>(istream& i, mod& m) {
    i >> m.val;
    m.val %= mod::p;
    if (m.val < 0) m.val += mod::p;
    return i;
  }
  friend ostream& operator<<(ostream& o, const mod& m) { return o << m.val; }
};

template<int sz, typename T>
struct matrix : public array<array<T, sz>, sz> {
  matrix() : array<array<T, sz>, sz>{} {}
  matrix(const T& val) : array<array<T, sz>, sz>{} {
    F0R (i, sz) (*this)[i][i] = val;
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
    matrix res{};
    F0R (r, sz) F0R (c, sz) F0R (k, sz) res[r][c] += a[r][k] * b[k][c];
    return res;
  }
  friend matrix operator*(matrix a, T v) {
    return a *= v;
  }
  friend matrix operator*(T v, matrix a) {
    return a *= v;
  }
};
using mat = matrix<2, mod>;
struct ST {
  using T = mat;
  const T unit{1};
  T merge(const T& l, const T& r) { return l * r; };
  int n;
  vector<T> data;
  ST(int n) : n(n), data(2 * n) {}
  ST(vector<T>& v) : n(SZ(v)), data(2 * SZ(v)) {
    copy(ALL(v), data.begin() + SZ(v));
    build();
  }
  void build() {
    for (int i = n - 1; i > 0; --i)
      data[i] = merge(data[i << 1], data[i << 1 | 1]);
  }
  T query(int l, int r) {
    T li = unit, ri = unit;
    for (l += n, r += n; l < r; r >>= 1, l >>= 1) {
      if (l & 1) li = merge(li, data[l++]);
      if (r & 1) ri = merge(data[--r], ri);
    }
    return merge(li, ri);
  }
  void update(int i, const T& val) {
    for (data[i += n] = val; i > 1; i >>= 1)
      data[i >> 1] = merge(data[i & ~1], data[i | 1]);
  }
};

mat get(char c) {
  mat res{};
  switch (c) {
  case 'H':
    res[0][0] = res[1][0] = 1;
    break;
  case 'S': case 'D':
    res[1][1] = res[0][1] = 1;
    break;
  case 'A': case 'E': case 'I': case 'O': case 'U':
    res[1][0] = res[0][1] = 1;
    break;
  case '?':
    res[0][0] = 19;
    res[0][1] = 7;
    res[1][0] = 6;
    res[1][1] = 20;
    break;
  default:
    res[0][0] = res[1][1] = 1;
  }
  return res;
}

int main() {
  ios_base::sync_with_stdio(0);
  cout.tie(0); cin.tie(0);

  int n, q; cin >> n >> q;
  string s; cin >> s;
  ST st(n);
  F0R (i, n) st.data[n + i] = get(s[i]);
  st.build();

  cout << st.query(0, n)[0][0] << endl;
  while (q--) {
    int idx; char c; cin >> idx >> c;
    st.update(idx - 1, get(c));
    cout << st.query(0, n)[0][0] << endl;
  }

  return 0;
}
