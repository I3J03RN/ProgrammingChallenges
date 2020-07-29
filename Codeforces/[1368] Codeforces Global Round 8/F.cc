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

vector<bool> lamp;
int n;

int query(int a, int b) {
  cout << 2 << ' ' << a + 1 << ' ' << b + 1 << endl;
  int x;
  cin >> x;
  assert(~x);
  --x;
  if (!lamp[x]) {
    x = ++x % n;
  }
  return x;
}

void solve() {
  cin >> n;
  lamp.assign(n, 0);
  int best = n / 2 - 1;
  int on = 0;

  int l = 0, r = 2, last = -1;
  while (on < best) {
    if (~last) {
      lamp[last] = lamp[r] = 1;
      int x = query(last, r);
      lamp[x] = 0;
      if (x == r) {
        last = -1;
      } else {
        r = (r + 2) % n;
        last = x;
      }
    } else {
      lamp[l] = lamp[r] = 1;
      int x = query(l, r);
      lamp[x] = 0;
      if (x == l) {
        r = (r + 2) % n;
      } else if (x == r) {
        l = (l + n - 2) % n;
      } else {
        last = x;
        l = (l + n - 2) % n;
        r = (r + 2) % n;
      }
    }
    ++on;
  }
  cout << 0 << endl;
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
