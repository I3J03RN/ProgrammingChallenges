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

constexpr int inf = (int)1e8;

int main() {
  ios_base::sync_with_stdio(0);
  cout.tie(0); cin.tie(0);

  int H, W; cin >> H >> W;
  set<tuple<int, int, int>> s;
  multiset<int> ms;
  F0R (i, W) {
    s.emplace(i, 1, 0);
    ms.insert(0);
  }

  FOR (i, 1, H + 1) {
    int a, b; cin >> a >> b; --a; --b;
    auto be = s.lower_bound(mt(a, (int)1e9, (int)1e9));
    be = prev(be);
    int base = inf;
    {
      auto [p, l, v] = *be; 
      if (p == a) {
        if (be != s.begin()) {
          auto [pp, len, vv] = *prev(be);
          base = vv + len;
        }
      } else {
        base = v + a - p;
      }
    }
    vector<tuple<int, int, int>> ne;
    if (auto [p, l, v] = *be; p < a) {
      ne.eb(p, a - p, v);
    }
    auto ed = be;
    for (;; ++ed) {
      ms.erase(ms.find(get<2>(*ed)));
      if (auto [p, l, v] = *ed; b < p + l) break;
    }
    ne.eb(a, b - a + 1, base);
    if (auto [p, l, v] = *ed; b + 1 < p + l) {
      ne.eb(b + 1, p + l - b - 1, v + (b - p) + 1);
    }
    s.erase(be, next(ed));
    for (auto t : ne) {
      ms.insert(get<2>(t));
      s.insert(t);
    }

    int sm = *ms.begin();
    cout << (sm >= inf ? -1 : sm + i) << endl;
  }
  
  return 0;
}
