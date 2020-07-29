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
double dir(pt a, pt b, pt c) {
  pt ab = b - a, ac = c - a;
  return ab.xx * ac.yy - ab.yy * ac.xx;
}
bool cw(pt a, pt b, pt c) { return dir(a, b, c) < 0; }
bool ccw(pt a, pt b, pt c) { return dir(a, b, c) > 0; }
// careful with inputs for n < 2
vector<pt> convexHull(vector<pt>& pts) {
  int n = SZ(pts);
  // sort(ALL(pts),
  //      [](pt a, pt b) { return mp(a.xx, a.yy) < mp(b.xx, b.yy); });
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

bool inTriangle(pt a, pt b, pt c, pt p) {
  return abs(-abs(dir(a, b, c)) + abs(dir(a, b, p)) + abs(dir(a, p, c)) + abs(dir(p, b, c))) < 1e-9;
}

bool inPolygon(vector<pt>& poly, pt p) {
  int l = 1, r = SZ(poly) - 2;
  while (l < r) {
    int mid = (l + r) / 2;
    if (cw(poly[0], poly[mid], p)) {
      l = mid + 1;
    } else {
      r = mid;
    }
  }
  return inTriangle(poly[0], poly[l], poly[l - 1], p);
}

double dot(pt a, pt b) {
  return real(a) * real(b) + imag(a) * imag(b);
}

double distToLineSegment(pt p, pt a, pt b) {
  pt ap = p - a, ab = b - a;
  double u = dot(ap, ab) / (abs(ab) * abs(ab));
  dout << dvar(p) << dvar(a) << dvar(b) << dvar(ab) << dvar(ap) << dvar(u) << endl;
  if (u < 0.0) return abs(p - a);  // a is closest
  if (u > 1.0) return abs(p - b);  // b is closest
  return abs(p - a - ab * u);      // closest is in segment.
}

template<class T>
bool collinear(complex<T> p, complex<T> q, complex<T> r) { return abs(dir(p, q, r)) < 1e-9; }

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);

  int c, r, o, casenr = 1;
  while (cin >> c >> r >> o, c || r || o) {
    vector<pt> cops, robbers;
    F0R (_, c) {
      double x, y;
      cin >> x >> y;
      cops.eb(x, y);
    }
    F0R (_, r) {
      double x, y;
      cin >> x >> y;
      robbers.eb(x, y);
    }
    sort(ALL(cops),
        [](pt a, pt b) { return mp(a.xx, a.yy) < mp(b.xx, b.yy); });
    sort(ALL(robbers),
        [](pt a, pt b) { return mp(a.xx, a.yy) < mp(b.xx, b.yy); });
    cops.resize(distance(cops.begin(), unique(ALL(cops))));
    robbers.resize(distance(robbers.begin(), unique(ALL(robbers))));
    bool copsl = 1, robbersl = 1;
    F0R (i, SZ(cops) - 2) {
      if (!collinear(cops[i], cops[i + 1], cops[i + 2])) {
        copsl = 0; break;
      }
    }
    F0R (i, SZ(robbers) - 2) {
      if (!collinear(robbers[i], robbers[i + 1], robbers[i + 2])) {
        robbersl = 0; break;
      }
    }
    
    if (SZ(cops) > 2 && !copsl) {
      cops = convexHull(cops);
    }
    if (SZ(robbers) > 2 && !robbersl) {
      robbers = convexHull(robbers);
    }
    cout << "Data set " << casenr++ << ":" << endl;
    dout << dvar(cops) << endl << dvar(robbers) << endl;
    while (o--) {
      double x, y;
      cin >> x >> y;
      pt p(x, y);
      bool safe = false, robbed = false;
      if (c > 2) {
        if (SZ(cops) > 2) {
          if (copsl) {
            safe = abs(distToLineSegment(p, cops[0], cops.back())) < 1e-9;
            dout << dvar(abs(distToLineSegment(p, cops[0], cops.back()))) << endl;
          } else {
            safe = inPolygon(cops, p);
          }
        } else if (SZ(cops) == 2) {
          safe = abs(distToLineSegment(p, cops[0], cops[1])) < 1e-9;
        } else if (SZ(cops) == 1) {
          safe = abs(cops[0] - p) < 1e-9;
        }
      }
      if (r > 2) {
        if (SZ(robbers) > 2) {
          if (robbersl) {
            robbed = abs(distToLineSegment(p, robbers[0], robbers.back())) < 1e-9;
          } else {
            robbed = inPolygon(robbers, p);
          }
        } else if (SZ(robbers) == 2) {
          robbed = abs(distToLineSegment(p, robbers[0], robbers[1])) < 1e-9;
        } else if (SZ(robbers) == 1) {
          robbed = abs(robbers[0] - p) < 1e-9;
        }
      }
      cout << "     Citizen at (" << (int) x << "," << (int) y << ") is ";
      if (safe) {
        cout << "safe";
      } else if (robbed) {
        cout << "robbed";
      } else {
        cout << "neither";
      }
      cout << '.' << endl;
    }
    cout << endl;
  }

  return 0;
}
