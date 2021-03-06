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
template<ll p>
struct mint {
  static constexpr ll mod = p;
  ll val;
  mint() : val(0) {}
  mint(ll val) : val(val % p) { if (this->val < 0) this->val += p; }
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


void solve() {
  int n; string s; cin >> n >> s;
  // int k = count(ALL(s), '?');
  mod ka = 1; //mod::pow(3, k);
  mod kk = 3;//mod::pow(3, max(0, k - 1));
  vector<vector<mod>> pre(n + 2, vector<mod>(3)), suf(n + 2, vector<mod>(3));
  F0R (i, n) {
    pre[i + 1] = pre[i];
    if (s[i] == '?') {
      for (auto& j : pre[i + 1]) j += kk;
    } else {
      pre[i + 1][s[i] - 'a'] += ka;
    }
  }
  for (int i = n; i; --i) {
    suf[i] = suf[i + 1];
    if (s[i - 1] == '?') {
      for (auto& j : suf[i]) j += kk;
    } else {
      suf[i][s[i - 1] - 'a'] += ka;
    }
  }
  dout << dvar(pre) << endl;
  dout << dvar(suf) << endl;
  vector<mod> asbs(n + 2), bscs(n + 2);
  FOR (i, 1, n + 1) {
    asbs[i] = asbs[i - 1];
    if (s[i - 1] == 'b' || s[i - 1] == '?') {
      asbs[i] += pre[i - 1][0];
    }
  }
  for (int i = n; i; --i) {
    bscs[i] = bscs[i + 1];
    if (s[i - 1] == 'b' || s[i - 1] == '?') {
      bscs[i] += suf[i + 1][2];
    }
  }
  dout << dvar(asbs) << endl;
  dout << dvar(bscs) << endl;
  mod ans = 0;
  FOR (i, 1, n + 1) {
    if (s[i - 1] == 'a' || s[i - 1] == '?') {
      ans += bscs[i + 1];
    }
    if (s[i - 1] == 'b' || s[i - 1] == '?') {
      ans += pre[i - 1][0] * suf[i + 1][2];
    }
    if (s[i - 1] == 'c' || s[i - 1] == '?') {
      ans += asbs[i - 1];
    }
  }
  cout << ans << endl;
}

int main() {
  ios_base::sync_with_stdio(0);
  cout.tie(0); cin.tie(0);

  int tt = 1;
  FOR (t, 1, tt + 1) {
    // cout << "Case #" << t << ": ";
    solve();
  }
  
  return 0;
}
