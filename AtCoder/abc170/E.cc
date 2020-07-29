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
#define pf push_front
#define eb emplace_back
#define pb push_back
#define mp make_pair
#define mt make_tuple
#define SZ(x) (int)(x).size()
#define endl '\n'
#define FOR(a, b, c) for (auto(a) = (b); (a) < (c); ++(a))
#define ROF(a, b, c) for (auto(a) = (b); (a) > (c); --(a))
#define F0R(a, b) FOR ((a), 0, (b))
#define R0F(a, b) ROF ((a), (b), -1)
#define CEIL(a, b) ((a) + (b)-1) / (b)
#define SET(a, b) memset((a), (b), sizeof(a))
template <class t>
bool ckmin(t& a, const t& b) {
  return a > b ? a = b, true : false;
}
template <class t>
bool ckmax(t& a, const t& b) {
  return a < b ? a = b, true : false;
}
#ifndef DEBUG
#define DEBUG 0
#endif
#define dout if (DEBUG) std::cerr
#define dvar(...) " [" << #__VA_ARGS__ ": " << (__VA_ARGS__) << "] "
template <class a, class b>
ostream& operator<<(ostream& o, const pair<a, b>& p);
template <class T>
struct IsC {
  template <class C>
  static char test(typename C::const_iterator*);
  template <class C>
  static int test(...);
  static const bool value = sizeof(test<T>(0)) == sizeof(char);
};
template <>
struct IsC<string> {
  static const bool value = false;
};
template <class C>
typename enable_if<IsC<C>::value, ostream&>::type operator<<(ostream& o, const C& c) {
  o << '[';
  for (auto it = c.begin(); it != c.end();)
      o << *it << (++it != c.end() ? ", " : "");
  return o << ']';
}
template <class a, class b>
ostream& operator<<(ostream& o, const pair<a, b>& p) {
  return o << '(' << p.fi << ", " << p.se << ')';
}


struct ST {
  int n;
  vi value;
  int inline left(int p) { return p << 1; }
  int inline right(int p) { return (p << 1) + 1; }
  int build(const vi& a, int p, int L, int R) {
    if (L == R) {
      return value[p] = a[L];
    } else {
      value[p] = max(build(a, left(p), L, (R + L) / 2),
                     build(a, right(p), (R + L) / 2 + 1, R));
      return value[p];
    }
  }
  int rmq(int p, int L, int R, int i, int j) {
    if (i > R || j < L) return numeric_limits<int>::max();
    if (i <= L && R <= j) return value[p];
    return min(rmq(left(p), L, (L + R) / 2, i, j),
               rmq(right(p), (L + R) / 2 + 1, R, i, j));
  }
  int update(int p, int L, int R, int i, int v) {
    if (L == i && R == i) return value[p] = v;
    if (i < L || R < i) return value[p];
    return value[p] = min(update(left(p), L, (L + R) / 2, i, v),
                          update(right(p), (L + R) / 2 + 1, R, i, v));
  }
  ST(int n) : n(n), value(n * 4, 0)  {}
  ST(const vi& a) : n(SZ(a)), value(SZ(a) * 4) {
    build(a, 1, 0, SZ(a) - 1);
  }
  int rmq(int i, int j) { return rmq(1, 0, n - 1, i, j); }
  void update(int i, int v) {
    update(1, 0, n - 1, i, v);
  }
  int size() { return n; }
};

const int mxN = 2e5 + 1;

multiset<int, greater<int>> ms[mxN];

const int inf = 2e9;

void solve() {
  int n, q;
  cin >> n >> q;
  vi as(n), bs(n);
  ST st(mxN);
  F0R (i, n) {
    cin >> as[i] >> bs[i];
    ms[bs[i]].insert(as[i]);
  }
  F0R (i, mxN) {
    if (SZ(ms[i])) {
      st.update(i, *ms[i].begin());
    } else {
      st.update(i, inf);
    }
  }
  while (q--) {
    int c, d;
    cin >> c >> d;
    c--;
    ms[bs[c]].erase(as[c]);
    st.update(bs[c], (SZ(ms[bs[c]]) ? *ms[bs[c]].begin() : inf));
    bs[c] = d;
    ms[bs[c]].insert(as[c]);
    st.update(bs[c], *ms[bs[c]].begin());

    cout << st.rmq(0, mxN - 1) << endl;
  }
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);

  int tt = 1;
  FOR (t, 1, tt + 1) {
      // cout << "Case #" << t << ": ";
      solve();
  }

  return 0;
}
