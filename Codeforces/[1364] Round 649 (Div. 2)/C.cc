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


struct FT {
  vi A;
  int n;
  FT(int n) : A(n + 1, 0), n(n) {}
  int inline LSOne(int i) { return i & (-i); }
  int query(int i) {
    int sum = 0;
    for (; i; i -= LSOne(i)) sum += A[i];
    return sum;
  }
  int query(int i, int j) { return query(j) - query(i - 1); }
  void adjust(int i, int adjustBy) {
    for (; i <= n; i += LSOne(i)) A[i] += adjustBy;
  }
  // lb assumes query(i, i) >= 0 forall i in [1, n]
  // returns min p >= 1, so that [1, p] >= sum
  // if [1, n] < sum, return n + 1
  int lb(int sum) {
    int pos = 0;
    for (int pw = 1 << 25; pw; pw >>= 1)
      if (pos + pw <= n && sum > A[pos | pw]) sum -= A[pos |= pw];
    if (sum) ++pos;
    return pos;
  }
};

void solve() {
  int n;
  cin >> n;
  vi as(n);
  F0R (i, n) cin >> as[i];
  vi cnt(n + 1);
  for (int i : as) ++cnt[i];
  bool ok = 1;
  vi bs(n);
  int ptr = 0;
  int next = -1;
  FT wrote(n * 2 + 10);
  F0R (i, n) {
    if (~next) {
      bs[i] = next;
      next = -1;
    } else {
      while (ptr < SZ(cnt) && cnt[ptr]) ++ptr;
      bs[i] = ptr++;
    }
    wrote.adjust(bs[i] + 1, 1);
    if (wrote.query(as[i]) != as[i]) {
      ok = 0;
      break;
    }
    if (--cnt[as[i]] == 0) {
      if (as[i] < ptr) {
        next = as[i];
      }
    }
  }
  if (ok) {
    for (int i : bs) cout << i << ' ';
    cout << endl;
  } else {
    cout << -1 << endl;
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
