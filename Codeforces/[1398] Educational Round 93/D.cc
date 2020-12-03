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

template<typename T, size_t dim>
struct tensor {
  vector<T> data;
  array<size_t, dim> ds;
  tensor(initializer_list<int> dims)
    : data(accumulate(ALL(dims), (size_t)1, multiplies<size_t>())) {
    copy(ALL(dims), ds.begin());
    for (int i = dim - 1; i; --i) {
      ds[i - 1] *= ds[i];
    }
    rotate(ds.begin(), 1 + ALL(ds));
    ds.back() = 1;
  }
  T& operator[](initializer_list<int> idxs) {
    size_t idx = 0;
    size_t i = 0;
    for (auto j : idxs) {
      idx += ds[i++] * j;
    }
    return data[idx];
  }
};

vi read(int n) {
  vi res(n); F0R (i, n) cin >> res[i];
  sort(ALL(res));
  return res;
}

int main() {
  ios_base::sync_with_stdio(0);
  cout.tie(0); cin.tie(0);

  vi v(3); F0R (i, 3) cin >> v[i]; 
  vvi vs(3);
  F0R (i, 3) {
    vs[i] = read(v[i]);
    vs[i].pb(0);
  }


  tensor<ll, 3> dp({v[0] + 2, v[1] + 2, v[2] + 2});

  vi i(3);
  for (i[0] = SZ(vs[0]) - 1; ~i[0]; --i[0]) {
    for (i[1] = SZ(vs[1]) - 1; ~i[1]; --i[1]) {
      for (i[2] = SZ(vs[2]) - 1; ~i[2]; --i[2]) {
        F0R (j, 8) {
          ll val = 0;
          if (j == 3) {
            val = vs[0][i[0]] * vs[1][i[1]];
          } else if (j == 5) {
            val = vs[0][i[0]] * vs[2][i[2]];
          } else if (j == 6) {
            val = vs[1][i[1]] * vs[2][i[2]];
          }
          ckmax(dp[{i[0], i[1], i[2]}],
                val + dp[{i[0] + (j & 1), i[1] + ((j >> 1) & 1), i[2] + ((j >> 2) & 1)}]);
        }
      }
    }
  }

  cout << dp[{0, 0, 0}] << endl;
  
  return 0;
}
