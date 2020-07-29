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

int calc(int n) {
  if (!n) return 0;
  return 1 + calc(n % __builtin_popcount(n));
}

ll pow(ll a, ll b, ll m) {
  if (m <= 0) return -1;
  ll res = 1;
  for (; b; b >>= 1, a = a * a % m)
    if (b & 1) res = res * a % m;
  return res;
}

int main() {
  ios_base::sync_with_stdio(0);
  cout.tie(0);

  int n; string s; cin >> n >> s;
  int ones = count(ALL(s), '1');

  vvi dp(2, vi(n));
  vi val(2);
  vi calc(n + 3);
  FOR (i, 1, n + 3) {
    int k = i % __builtin_popcount(i);
    dout << dvar(i, k) << endl;
    calc[i] = 1 + calc[k];
  }
  F0R (i, n) {
    if (s[n - 1 - i] == '1') {
      dp[0][n - 1 - i] = pow(2, i, ones + 1);
      dp[1][n - 1 - i] = pow(2, i, ones - 1);
    }
    val[0] = (val[0] + dp[0][n - 1 - i]) % (ones + 1); 
    val[1] = (val[1] + dp[1][n - 1 - i]) % max(1, ones - 1); 
  }
  dout << dvar(ones) << endl << dvar(dp) << endl << dvar(val) << endl;
  F0R (i, n) {
    if (s[i] == '0') {
      int res = (val[0] + (int)pow(2, n - 1 - i, ones + 1)) % (ones + 1);
      cout << 1 + calc[res] << endl;
    } else {
      if (ones == 1) cout << 0 << endl;
      else cout << 1 + calc[(val[1] - dp[1][i] + ones - 1) % (ones - 1)] << endl;
    }
  }

  
  
  
  return 0;
}
