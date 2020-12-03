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
#define dvar(...) " \x1b[35m[" << #__VA_ARGS__ ": " << mt(__VA_ARGS__) << "]\x1b[0m "
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

template<ll p>
struct mint {
  static constexpr ll mod = p;
  ll val;
  mint() : val(0) {}
  mint(ll v) : val(v % p) { if (val < 0) val += p; }
  mint& operator+=(const mint& o) {
    val = (val + o.val) % p;
    return *this;
  }
  mint& operator-=(const mint& o) {
    val = (val - o.val + p) % p;
    return *this;
  }
  mint& operator*=(const mint& o) {
    val = val * o.val % p;
    return *this;
  }
  mint& operator/=(mint o) { return (*this) *= pow(o, p - 2); }
  mint& operator++() { return (*this) += 1; }
  mint operator++(int) { return ++(*this) - 1; }
  mint& operator--() { return (*this) -= 1; }
  mint operator--(int) { return --(*this) + 1; }
  mint friend operator+(mint a, const mint& b) { return a += b; }
  mint friend operator-(mint a, const mint& b) { return a -= b; }
  mint friend operator*(mint a, const mint& b) { return a *= b; }
  mint friend operator/(mint a, const mint& b) { return a /= b; }
  static mint pow(mint a, mint b) {
    mint res = 1;
    for (; b.val; b.val >>= 1, a = a * a)
      if (b.val & 1) res = res * a;
    return res;
  }
  friend istream& operator>>(istream& i, mint& m) {
    i >> m.val;
    m.val %= p;
    if (m.val < 0) m.val += p;
    return i;
  }
  friend ostream& operator<<(ostream& o, const mint& m) { return o << m.val; }
};
using mod1 = mint<(ll)1e9 + 7ll>;
using mod2 = mint<998244353ll>;
using mod = mod1;

vector<mod> fac;

mod choose(int n, int k) {
  if (k > n) return 0;
  return fac[n] / (fac[k] * fac[n - k]);
}

mod solve(int n, int m, int l) {
  dout << dvar(n, m, l) << endl;
  if (n == 0 && m == 0 && l == 0) return 1;
  if (n < l) return 0;
  mod sum = 0;
  FOR (i, l - 1, min(m + 1, 2 * l - 1)) {
    int ex = i - (l - 1);
    mod t = fac[l] * choose(n, l) * choose(l - 1, ex) / 2;
    F0R (j, l + 1) sum += t * solve(n - l, m - i, j);
  }
  return sum;
}

int main() {
  ios_base::sync_with_stdio(0);
  cout.tie(0); cin.tie(0);

  fac.resize(500);
  fac[0] = 1;
  FOR (i, 1, 500) fac[i] = fac[i - 1] * i;

  int n, m, l; cin >> n >> m >> l;
  cout << solve(n, m, l) << endl;
  
  return 0;
}
