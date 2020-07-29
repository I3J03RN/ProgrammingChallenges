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

void solve() {
  int n;
  cin >> n;
  vi x1(n), x2(n), y1(n), y2(n);
  F0R (i, n) {
    cin >> x1[i] >> y1[i] >> x2[i] >> y2[i];
    if (x1[i] > x2[i]) {
      swap(x1[i], x2[i]);
      swap(y1[i], y2[i]);
    }
  }
  int q;
  cin >> q;
  while (q--) {
    int x, y;
    cin >> x >> y;
    while (1) {
      dout << dvar(x) << dvar(y) << endl;
      pair<double, int> best{-1, -1};
      F0R (i, n) {
        if (x1[i] < x && x < x2[i]) {
          double m = (double)(y2[i] - y1[i]) / (x2[i] - x1[1]);
          double h = m * (x - x1[i]) + y1[i];
          dout << dvar(i) << dvar(m) << dvar(h) << endl;
          if (h <= y) {
            ckmax(best, mp(h, i));
          }
        }
      }
      if (best.se == -1) break;
      dout << dvar(best) << endl;
      if (y1[best.se] < y2[best.se]) {
        y = y1[best.se];
        x = x1[best.se];
      } else {
        y = y2[best.se];
        x = x2[best.se];
      }
    }
    cout << x << endl;
  }
  
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);

  int tt = 1;
  cin >> tt;
  FOR (t, 1, tt + 1) {
    if (t > 1) cout << endl;
    // cout << "Case #" << t << ": ";
    solve();
  }

  return 0;
}
