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

#define xx real()
#define yy imag()

using pt = complex<double>;

// dot product of ab and ac
double dir(pt a, pt b, pt c) {
  pt ab = b - a, ac = c - a;
  return ab.xx * ac.yy - ab.yy * ac.xx;
}

bool cw(pt a, pt b, pt c) {
  return dir(a, b, c) < 0;
}

bool ccw(pt a, pt b, pt c) {
  return dir(a, b, c) > 0;
}

// careful with inputs for n < 2
vector<pt> convexHull(vector<pt>& pts) {
  int n = SZ(pts);
  sort(ALL(pts), [](pt a, pt b) { return mp(a.real(),  a.imag()) < mp(b.real(), b.imag()); });
  vector<pt> up, down;
  up.eb(pts[0]); down.eb(pts[0]);
  FOR (i, 1, n) {
    if (i == n - 1 || ccw(pts[0], pts[n - 1], pts[i])) {
      while (SZ(up) > 1 && ccw(up[SZ(up) - 2], up[SZ(up) - 1], pts[i]))
        up.pop_back();
      up.eb(pts[i]);
    }
    if (i == n - 1 || cw(pts[0], pts[n - 1], pts[i])) {
      while (SZ(down) > 1 && cw(down[SZ(down) - 2], down[SZ(down) - 1], pts[i]))
        down.pop_back();
      down.eb(pts[i]);
    }
  }
  vector<pt> ans(up);
  ans.insert(ans.end(), 1 + RALL(down));
  return ans;
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);

  int ts, casenr = 1;
  while (cin >> ts, ts) {
    if (casenr > 1) cout << endl;
    vector<pt> traps;
    F0R (_, ts) {
      double x, y;
      cin >> x >> y;
      traps.eb(x, y);
    }
    vector<pt> ans = convexHull(traps);
    if (SZ(ans) == 1) ans.pb(ans[0]);
    cout << "Region #" << casenr++ << ":" << endl;
    F0R (i, SZ(ans)) {
      cout << fixed << setprecision(1) << ans[i] << "-\n"[i == SZ(ans) - 1]; 
    }
    double len = 0;
    F0R (i, SZ(ans) - 1) {
      len += abs(ans[i] - ans[i + 1]);
    }
    cout << "Perimeter length = " << setprecision(2) << len << endl;
  }

  return 0;
}
