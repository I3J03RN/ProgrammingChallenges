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

// #define xx real()
// #define yy imag()

// using pt = complex<double>;

// double dir(pt a, pt b, pt c) {
//   pt ab = b - a, ac = c - a;
//   return ab.xx * ac.yy - ab.yy * ac.xx;
// }

// bool cw(pt a, pt b, pt c) {
//   return dir(a, b, c) < 0;
// }

// bool ccw(pt a, pt b, pt c) {
//   return dir(a, b, c) > 0;
// }

// // careful with inputs for n < 2
// vector<pt> convexHull(vector<pt>& pts) {
//   int n = SZ(pts);
//   sort(ALL(pts), [](pt a, pt b) { return mp(a.real(),  a.imag()) < mp(b.real(), b.imag()); });
//   vector<pt> up, down;
//   up.eb(pts[0]); down.eb(pts[0]);
//   FOR (i, 1, n) {
//     if (i == n - 1 || ccw(pts[0], pts[n - 1], pts[i])) {
//       while (SZ(up) > 1 && ccw(up[SZ(up) - 2], up[SZ(up) - 1], pts[i]))
//         up.pop_back();
//       up.eb(pts[i]);
//     }
//     if (i == n - 1 || cw(pts[0], pts[n - 1], pts[i])) {
//       while (SZ(down) > 1 && cw(down[SZ(down) - 2], down[SZ(down) - 1], pts[i]))
//         down.pop_back();
//       down.eb(pts[i]);
//     }
//   }
//   vector<pt> ans(up);
//   ans.insert(ans.end(), 1 + RALL(down));
//   return ans;
// }


#define xx real()
#define yy imag()
const double EPS = 1e-9;
const double INF = numeric_limits<double>::max();
using pt = complex<double>;
struct Line {
  double a, b, c;
};  // ax + by + c = 0
double dot(pt a, pt b) { return a.xx * b.xx + a.yy * b.yy; }
double cross(pt a, pt b) { return a.xx * b.yy - a.yy * b.xx; }
double dir(pt a, pt b, pt c) { return cross(b - a, c - a); }
bool cw(pt a, pt b, pt c) { return dir(a, b, c) < 0; }
bool ccw(pt a, pt b, pt c) { return dir(a, b, c) > 0; }
bool collinear(pt a, pt b, pt c) { return abs(dir(a, b, c)) < EPS; }
// Angle between a and b with o as origin (ccw).
// Return value in [0, 2PI)
double angle(pt a, pt b) {
  double ang = arg(a) - arg(b);
  return ang < 0 ? ang + 2 * M_PI : ang;
}
double angle(pt a, pt b, pt o) { return angle(b - o, a - o); }
// Theta in radiens
pt rotate(pt a, double theta) { return a * polar(1.0, theta); }
Line ptToLine(pt p1, pt p2) {
  if (abs(real(p1) - real(p2)) < EPS) {
    return {1.0, 0.0, -real(p1)};
  } else {
    double a = -(imag(p1) - imag(p2)) / (real(p1) - real(p2)),
           c = -(a * real(p1)) - imag(p2);
    return {a, 1.0, c};
  }
}
bool areParallel(Line l1, Line l2) {
  return abs(l1.a - l2.a) < EPS && abs(l1.b - l2.b) < EPS;
}
bool areSame(Line l1, Line l2) {
  return areParallel(l1, l2) && abs(l1.c - l2.c) < EPS;
}
pt intersectPt(Line l1, Line l2) {
  // Does not handle if same or parrallel
  if (areParallel(l1, l2)) return pt(-INF, -INF);
  double x =
      (l2.b * l1.c - l1.b * l2.c) / (l2.a * l1.b - l1.a * l2.b);
  double y;
  if (abs(l1.b) < EPS)
    y = -(l1.a * x + l1.c);
  else
    y = -(l2.a * x + l2.c);
  return pt(x, y);
}
double distToLine(pt p, pt a, pt b, bool segment = false) {
  pt ap = p - a, ab = b - a;
  double u = dot(ap, ab) / (abs(ab) * abs(ab));
  if (segment) {
    if (u < 0.0) return abs(p - a);  // a is closest
    if (u > 1.0) return abs(p - b);  // b is closest
  }
  return abs(p - a - ab * u);      // closest is in segment.
}

// careful with inputs for n < 2
vector<pt> convexHull(vector<pt>& pts) {
  int n = SZ(pts);
  sort(ALL(pts),
       [](pt a, pt b) { return mp(a.xx, a.yy) < mp(b.xx, b.yy); });
  vector<pt> up, down;
  up.eb(pts[0]); down.eb(pts[0]);
  FOR (i, 1, n) {
    if (i == n - 1 || ccw(pts[0], pts[n - 1], pts[i])) {
      while (SZ(up) > 1 &&
             ccw(up[SZ(up) - 2], up[SZ(up) - 1], pts[i]))
        up.pop_back();
      up.eb(pts[i]);
    }
    if (i == n - 1 || cw(pts[0], pts[n - 1], pts[i])) {
      while (SZ(down) > 1 &&
             cw(down[SZ(down) - 2], down[SZ(down) - 1], pts[i]))
        down.pop_back();
      down.eb(pts[i]);
    }
  }
  vector<pt> ans(up);
  ans.insert(ans.end(), 1 + RALL(down));
  return ans;
}

void solve() {
  double init;
  int n;
  cin >> init >> n;
  vector<pt> pts;
  while (n--) {
    double x, y;
    cin >> x >> y;
    pts.eb(x, y);
  }
  pts = convexHull(pts);
  double len = 0;
  F0R (i, SZ(pts) - 1) {
    len += abs(pts[i] - pts[i + 1]);
  }
  cout << fixed << setprecision(5) << max(init, len) << endl;
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);

  int tt = 1;
  cin >> tt;
  FOR (t, 1, tt + 1) {
      // cout << "Case #" << t << ": ";
      solve();
  }

  return 0;
}
