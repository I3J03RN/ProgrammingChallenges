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

int main() {
  ios_base::sync_with_stdio(0);
  cout.tie(0);

  int n, m, k;
  ll x, y;
  cin >> n >> m >> x >> k >> y;
  vi as(n), bs(m), pos(n + 1, -1);
  F0R (i, n) cin >> as[i];
  F0R (i, m) cin >> bs[i];
  F0R (i, n) pos[as[i]] = i;
  int mx = -1;
  for (int a : bs) {
    if (pos[a] == -1 || pos[a] < mx) {
      cout << -1 << endl;
      return 0;
    }
    mx = pos[a];
  }
  dout << "hui" << endl;
  ll cost = 0;
  // min cost remove [l, r) from A
  auto rm = [&](int l, int r) {
              int len = r - l;
              if (!len) return 0ll;
              int mxv = *max_element(as.begin() + l, as.begin() + r);
              bool use = 0;
              if (l == 0) {
                use = as[r] > mxv;
              } else if (r == n) {
                use = as[l - 1] > mxv;
              } else {
                use = max(as[l - 1], as[r]) > mxv;
              }
              if (len < k) {
                if (!use) return -1ll;
                return len * y;
              } 
              ll c = 0;
              c += (len % k) * y;
              len -= (len % k);
              if (!use) {
                len -= k;
                c += x;
              }
              c += min(len / k * x, len * y);
              return c;
            };
  ll c = rm(0, pos[bs[0]]);
  dout << dvar(c) << endl;
  if (c == -1) {
    cout << -1 << endl;
    return 0;
  } 
  cost += c;
  c = rm(pos[bs[m - 1]] + 1, n);
  dout << dvar(c) << endl;
  if (c == -1) {
    cout << -1 << endl;
    return 0;
  } 
  cost += c;
  
  F0R (i, m - 1) {
    c = rm(pos[bs[i]] + 1, pos[bs[i + 1]]);
    dout << dvar(c) << endl;
    if (c == -1) {
      cout << -1 << endl;
      return 0;
    }
    cost += c;
  }

  cout << cost << endl;

  return 0;
}
