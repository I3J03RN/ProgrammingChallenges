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

using pt = complex<double>;

vector<double> rs, placed;
int n;

bool intersect(double x1, double r1, double x2, double r2) {
  return abs(x1 - x2) * abs(x1 - x2) + abs(r1 - r2) * abs(r1 - r2) <= (r1 + r2) * (r1 + r2);
}

bool placeable(double x, double r) {
  F0R (i, n) {
    if (placed[i] >= 0 && intersect(placed[i], rs[i], x, r)) return 0; 
  }
  return 1;
}

const double eps = 1e-7;

double dfs(int i = 0, int last = -1) {
  if (i == n) {
    double l = 1e9, r = 0;
    F0R (j, n) {
      ckmax(r, placed[j] + rs[j]);
      ckmin(l, placed[j] - rs[j]);
    }
    return r - l;
  }
  double best = 1e9;
  if (i == 0) {
    F0R (j, n) {
      placed[j] = rs[j];
      ckmin(best, dfs(i + 1, j));
      placed[j] = -1.0;
    }
  } else {
    F0R (j, n) {
      if (placed[j] < 0) {
        double l = placed[last], r = placed[last] + rs[last] + rs[j] + 100000;
        while (abs(l - r) > eps) {
          double mid = (l + r) / 2;
          if (placeable(mid, rs[j])) {
            r = mid;
          } else {
            l = mid;
          }
        }
        placed[j] = l;
        ckmin(best, dfs(i + 1, j));
        placed[j] = -1.0;
      }
    }
  }
  return best;
}

void solve() {
  cin >> n;
  placed.assign(n, -1);
  rs.assign(n, 0);
  F0R (i, n) cin >> rs[i];
  cout << fixed << setprecision(3) << dfs() << endl;
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
