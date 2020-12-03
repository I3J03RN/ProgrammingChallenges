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

struct ST {
  using T = ll;
  const int n, h;
  const T unit = 0;
  ll merge(ll a, ll b) {
    return a + b;   
  };
  vector<T> data, inc;
  ST(int sz) : n{sz}, h(sizeof(int) * 8 - __builtin_clz(n)), data(2 * n, unit), inc(n, unit) {}
  void build() {
    for (int i = n - 1; i; --i)
      data[i] = merge(data[i << 1], data[i << 1 | 1]);
  }
  void apply(int p, ll v, int k) {
    data[p] += v * k;
    if (p < n) inc[p] += v;
  }
  void build(int p) {
    int k = 2;
    while (p > 1) {
      p >>= 1;
      data[p] = data[p << 1] + data[p << 1 | 1] + inc[p] * k;
      k <<= 1;
    }
  }
  void push(int p) {
    for (int s = h, k = 1 << (h - 1); s > 0; --s, k >>= 1) {
      int i = p >> s;
      if (inc[i] != 0) {
        apply(i << 1, inc[i], k);
        apply(i << 1 | 1, inc[i], k);
        inc[i] = 0;
      }
    }
  }
  T query(int l, int r) {
    push(l + n); push(r + n - 1);
    T res = 0;
    for (l += n, r += n; l < r; r >>= 1, l >>= 1) {
      if (l & 1) res += data[l++];
      if (r & 1) res += data[--r];
    }
    return res;
  }
  void increase(int l, int r, ll v = 1) {
    push(l + n); push(r + n - 1);
    int l0 = l + n, r0 = r + n, k = 1;
    for (l += n, r += n; l < r; l >>= 1, r >>= 1, k <<= 1) {
      if (l & 1) apply(l++, v, k);
      if (r & 1) apply(--r, v, k);
    }
    build(l0); build(r0 - 1);
  }
};


int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);

  int n; cin >> n;
  string s; cin >> s;
  
  ST st(n);
  ll ans = 0;
  int cnt = 0;
  F0R (i, n) {
    if (s[i] == '0') {
      cnt = 0;
    } else {
      ++cnt;  
      int l = 0, r = i - cnt + 1;
      while (l < r) {
        int m = (l + r) / 2;
        if (st.query(m, m + 1) > cnt - 1) {
          l = m + 1;
        } else {
          r = m;
        }
      }
      st.increase(l, i + 1);
    }
    ans += st.query(0, i + 1);
  }
  cout << ans << endl;
  
  return 0;
}
