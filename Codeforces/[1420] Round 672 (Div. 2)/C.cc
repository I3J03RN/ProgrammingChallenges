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
//#define endl '\n'
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



// struct ST {
//   using T = vector<vector<ll>>;
//   const T unit = vector<vector<ll>>(2, vector<ll>(2));;
//   T merge(T l, T r) {
//     T res(2, vector<ll>(2));
//     res[0][0] = max({l[0][0], r[0][0], l[0][0] + r[1][0], l[0][1] + r[0][0]});
//     res[0][1] = max({l[0][1], r[0][1], l[0][0] + r[1][1], l[0][1] + r[0][1]});
//     res[1][0] = max({l[1][0], r[1][0], l[1][0] + r[1][0], l[1][1] + r[0][0]});
//     res[1][1] = max({l[1][1], r[1][1], l[1][0] + r[1][1], l[1][1] + r[0][1]});
//     // res[0][0] = max({l[0][0] + r[1][0], l[0][1] + r[0][0]});
//     // res[0][1] = max({l[0][0] + r[1][1], l[0][1] + r[0][1]});
//     // res[1][0] = max({l[1][0] + r[1][0], l[1][1] + r[0][0]});
//     // res[1][1] = max({l[1][0] + r[1][1], l[1][1] + r[0][1]});
//     return res;
//   };
//   int n;
//   vector<T> data;
//   ST(int n) : n(n), data(2 * n, vector<vector<ll>>(2, vector<ll>(2))) {}
//   ST(vector<T>& v) : n(SZ(v)), data(2 * SZ(v)) {
//     copy(ALL(v), data.begin() + SZ(v));
//     build();
//   }
//   void build() {
//     for (int i = n - 1; i; --i)
//       data[i] = merge(data[i << 1], data[i << 1 | 1]);
//   }
//   T query(int l, int r) {
//     T li = unit, ri = unit;
//     for (l += n, r += n; l < r; r >>= 1, l >>= 1) {
//       if (l & 1) li = merge(li, data[l++]);
//       if (r & 1) ri = merge(data[--r], ri);
//     }
//     return merge(li, ri);
//   }
//   void update(int i, T val) {
//     for (data[i += n] = val; i > 1; i >>= 1)
//       data[i >> 1] = merge(data[i & ~1], data[i | 1]);
//   }
// };

// vector<vector<ll>> base(int n) {
//   vector<vector<ll>> res(2, vector<ll>(2));
//   res[0][0] = n;
//   res[1][1] = -n;
//   return res;
// }

struct node {
  ll pp, pn, np, nn; 
  node(ll pp, ll pn, ll np, ll nn) : pp(pp), pn(pn), np(np), nn(nn) {}
  node(ll n) : pp(n), pn(0), np(0), nn(-n) {}
  node() : pp(0), pn(0), np(0), nn(0) {}
};

struct ST {
  using T = node;
  const T unit{};
//     res[0][0] = max({l[0][0], r[0][0], l[0][0] + r[1][0], l[0][1] + r[0][0]});
//     res[0][1] = max({l[0][1], r[0][1], l[0][0] + r[1][1], l[0][1] + r[0][1]});
//     res[1][0] = max({l[1][0], r[1][0], l[1][0] + r[1][0], l[1][1] + r[0][0]});
//     res[1][1] = max({l[1][1], r[1][1], l[1][0] + r[1][1], l[1][1] + r[0][1]});
  T merge(const T& l, const T& r) {
    return T(max(l.pp + r.np, l.pn + r.pp),
             max(l.pp + r.nn, l.pn + r.pn),
             max(l.np + r.np, l.nn + r.pp),
             max(l.np + r.nn, l.nn + r.pn));
  };
  int n;
  vector<T> data;
  ST(int n) : n(n), data(2 * n) {}
  ST(vector<T>& v) : n(SZ(v)), data(2 * SZ(v)) {
    copy(ALL(v), data.begin() + SZ(v));
    build();
  }
  void build() {
    for (int i = n - 1; i; --i)
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
  void update(int i, T val) {
    for (data[i += n] = val; i > 1; i >>= 1)
      data[i >> 1] = merge(data[i & ~1], data[i | 1]);
  }
};


void solve() {
  int n, q; cin >> n >> q;
  vi as(n); F0R (i, n) cin >> as[i];
  ST st(n);
  F0R (i, n) {
    st.data[i + n] = node(as[i]);
  }
  st.build();
  cout << st.query(0, n).pp << endl;
  while (q--) {
    int a, b;
    cin >> a >> b; --a; --b;
    swap(as[a], as[b]);
    st.update(a, node(as[a]));
    st.update(b, node(as[b]));
    cout << st.query(0, n).pp << endl;
  }
}

int main() {
  ios_base::sync_with_stdio(0);
  cout.tie(0); cin.tie(0);

  int tt = 1;
  cin >> tt;
  FOR (t, 1, tt + 1) {
    // cout << "Case #" << t << ": ";
    solve();
  }
  
  return 0;
}
