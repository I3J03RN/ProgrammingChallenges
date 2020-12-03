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

struct FT {
  using T = ll;
  vector<T> A;
  int n;
  FT(int n) : A(n + 1, 0), n(n) {}
  int inline LSOne(int i) { return i & (-i); }
  T query(int i) {
    T sum = 0;
    for (; i; i -= LSOne(i)) sum += A[i];
    return sum;
  }
  T query(int i, int j) { return query(j) - query(i - 1); }
  void update(int i, T add) {
    dout << dvar(i) << endl; dout.flush();
    for (; i <= n; i += LSOne(i)) A[i] += add;
  }
  // lb assumes query(i, i) >= 0 forall i in [1, n]
  // returns min p >= 1, so that [1, p] >= sum
  // if [1, n] < sum, return n + 1
  int lb(T sum) {
    int pos = 0;
    for (int pw = 1 << 25; pw; pw >>= 1)
      if (pos + pw <= n && sum > A[pos | pw]) sum -= A[pos |= pw];
    return pos + !!sum;
  }
};

int main() {
  ios_base::sync_with_stdio(0);
  cout.tie(0); cin.tie(0);

  int n; cin >> n;
  vector<pair<int, ll>> qs(n); F0R (i, n) cin >> qs[i].fi >> qs[i].se;
  vector<pair<ll, int>> ps; ps.reserve(n);
  F0R (i, n) {
    if (qs[i].se > 0) {
      ps.eb(qs[i].se, i);
    }
  }
  sort(RALL(ps));
  vi pos(n, -1);
  F0R (i, SZ(ps)) {
    pos[ps[i].se] = i;
  }

  FT filled(n);
  FT ft(n);
  set<ll> fires;
  map<ll, int> fpos, lpos;

  int x2 = 0;
  ll sum = 0;
  F0R (i, n) {
    auto [t, d] = qs[i];
    dout << dvar(t, d) << endl;
    sum += d;
    if (t) {
      if (d > 0) {
        ++x2;
        lpos[d] = pos[i];
        filled.update(pos[i] + 1, 1);
        ft.update(pos[i] + 1, d);
      } else {
        --x2;
        dout << dvar(lpos[-d]) << endl;
        filled.update(lpos[-d] + 1, -1);     
        ft.update(lpos[-d] + 1, d);
      }
    } else {
      if (d > 0) {
        fires.insert(d);
        fpos[d] = pos[i];
        filled.update(pos[i] + 1, 1);
        ft.update(pos[i] + 1, d);
      } else {
        fires.erase(-d);
        filled.update(fpos[-d] + 1, -1);
        ft.update(fpos[-d] + 1, d);
      }
    }
    int lb = filled.lb(x2);
    ll extra = lb ? ft.query(lb) : 0;
    ll last = lb ? ft.query(lb, lb) : 0;
    if (SZ(fires)) {
      if (*fires.rbegin() < last) {
        extra += *fires.rbegin() - last;
      }
    } else {
      extra -= last;
    }
    cout << sum + extra << endl;
  }
  
  return 0;
}
