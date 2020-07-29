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
template<typename T> struct range : public pair<T, T> {
  template<typename U> struct it : iterator<forward_iterator_tag, U> {
    U v;
    it(U vv) : v(vv) {}
    operator U&() { return v; }
    U operator*() { return v; }
  };
  range(T b, T e) : pair<T, T>(b, e) {}
  range(T e) : pair<T, T>(static_cast<T>(0), e) {}
  it<T> begin() { return this->fi; }
  it<T> end() { return this->se; }
  bool in(T v) { return this->fi <= v && v < this->se; }
};

struct mod {
  static const ll p = 998244353;
  ll val;
  mod() : val(0) {}
  mod(ll val) : val(val % p) { if (this->val < 0) this->val += p; }
  mod& operator+=(mod o) {
    val = (val + o.val) % p;
    return *this;
  }
  mod& operator-=(mod o) {
    val = (val - o.val + p) % p;
    return *this;
  }
  mod& operator*=(mod o) {
    val = val * o.val % p;
    return *this;
  }
  mod& operator/=(mod o) { return (*this) *= pow(o, p - 2); }
  mod& operator++() { return (*this) += 1; }
  mod operator++(int) { return ++(*this) - 1; }
  mod& operator--() { return (*this) -= 1; }
  mod operator--(int) { return --(*this) + 1; }
  mod friend operator+(mod a, mod b) { return a += b; }
  mod friend operator-(mod a, mod b) { return a -= b; }
  mod friend operator*(mod a, mod b) { return a *= b; }
  mod friend operator/(mod a, mod b) { return a /= b; }
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
  friend ostream& operator<<(ostream& o, mod m) { return o << m.val; }
};

struct f {
  mod a, b;
  f() : a(0), b(0) {}
  f(mod a, mod b) : a(a), b(b) {}
  mod calc(mod x) {
    return a * x + b;
  }
};

struct ST {
  using T = f;
  const T unit = f(1, 0);
  T merge(T l, T r) { return f(l.a * r.a, r.a * l.b + r.b); };
  int n;
  vector<T> data;
  ST(vector<T>& v) : n(SZ(v)), data(2 * SZ(v)) {
    copy(ALL(v), data.begin() + SZ(v));
    build();
  }
  void build() {
    for (int i = n - 1; i > 0; --i)
      data[i] = merge(data[i << 1], data[i << 1 | 1]);
  }
  ST(int n) : n(n), data(2 * n) {}
  T query(int l, int r) {
    l += n; r += n;
    T li = unit, ri = unit;
    for (; l < r; r >>= 1, l >>= 1) {
      if (l & 1) li = merge(li, data[l++]);
      if (r & 1) ri = merge(data[--r], ri);
    }
    return merge(li, ri);
  }
  void assign(int i, T val) {
    for (data[i += n] = val; i > 1; i >>= 1) {
      data[i >> 1] = merge(data[i & ~1], data[i | 1]);
    }
  }
};

void solve() {
  int n, q;
  cin >> n >> q;
  ST st(n);
  F0R (i, n) cin >> st.data[n + i].a >> st.data[n + i].b;
  st.build();
  while (q--) {
    int t, p, c, d;
    cin >> t >> p >> c >> d;
    if (t) {
      cout << st.query(p, c).calc(d) << endl;
    } else {
      st.assign(p, f(c, d));
    }
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
