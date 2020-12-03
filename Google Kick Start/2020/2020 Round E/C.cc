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
  vector<ll> A;
  int n;
  FT(int n) : A(n + 1, 0), n(n) {}
  int inline LSOne(int i) { return i & (-i); }
  ll query(int i) {
    ll sum = 0;
    for (; i; i -= LSOne(i)) sum += A[i];
    return sum;
  }
  ll query(int i, int j) { return query(j) - query(i - 1); }
  void update(int i, ll add) {
    for (; i <= n; i += LSOne(i)) A[i] += add;
  }
  // lb assumes query(i, i) >= 0 forall i in [1, n]
  // returns min p >= 1, so that [1, p] >= sum
  // if [1, n] < sum, return n + 1
  int lb(ll sum) {
    int pos = 0;
    for (int pw = 1 << 25; pw; pw >>= 1)
      if (pos + pw <= n && sum > A[pos | pw]) sum -= A[pos |= pw];
    if (sum) ++pos;
    return pos;
  }
};

void solve() {
  int n; cin >> n;
  vector<ll> es(n + 1), rs(n + 1);
  FOR (i, 1, n + 1) cin >> es[i] >> rs[i];
  FT ft(n);
  FOR (i, 1, n + 1) ft.update(i, es[i]);
  vector<pair<ll, int>> rm; rm.reserve(n);
  FOR (i, 1, n + 1) {
    rm.eb(es[i] + rs[i], i);
  }
  sort(RALL(rm)); int idx = 0;
  ll all = accumulate(ALL(es), 0ll);
  ll best = numeric_limits<ll>::max(); int rmed = 0;
  FOR (i, 1, n + 1) {
    if (all - es[i] < rs[i]) {
      best = all + ft.query(i - 1);
      break;
    }
  }
  if (best < numeric_limits<ll>::max()) {
    set<int> q;
    while (idx < SZ(rm) && all < rm[idx].fi) {
      q.insert(rm[idx++].se);
    }
    FOR (r, 1, n) {
      int gone = *q.begin(); q.erase(q.begin());
      ft.update(gone, -es[gone]);
      all -= es[gone];
      while (idx < SZ(rm) && all < rm[idx].fi) {
        q.insert(rm[idx++].se);
      }
      if (q.empty()) {
        rmed = r;
        best = numeric_limits<ll>::max();
        break;
      }
      int nxt = *q.begin();
      if (ckmax(best, all + ft.query(nxt - 1))) {
        rmed = r;
      }
    }
  } 
  if (best == numeric_limits<ll>::max()) {
    cout << rmed << ' ' << "INDEFINITELY" << endl;
  } else {
    cout << rmed << ' ' << best << endl;
  }
}

int main() {
  ios_base::sync_with_stdio(0);
  cout.tie(0); cin.tie(0);

  int tt = 1;
  cin >> tt;
  FOR (t, 1, tt + 1) {
    cout << "Case #" << t << ": ";
    solve();
  }
  
  return 0;
}
