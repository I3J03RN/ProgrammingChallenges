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


const int N = 1e7 + 10;
int lp[N+1];
vector<int> pr;
void sieve() {
  for (int i=2; i<=N; ++i) {
      if (lp[i] == 0) {
          lp[i] = i;
          pr.push_back (i);
      }
      for (int j=0; j<(int)pr.size() && pr[j]<=lp[i] && i*pr[j]<=N; ++j)
          lp[i * pr[j]] = pr[j];
  }
}

void solve() {
  FOR (i, 2, 1001) {
    if (lp[i] == i) continue;
    int p1 = lp[i], p2 = -1;
    int it = i / lp[i];
    while (1) {
      if (it == lp[it]) break;
      if (lp[it] != p1) {
        p2 = lp[it];
        break;
      }
      it = lp[it];
    }
    dout << dvar(i) << dvar(p1) << dvar(p2) << endl;
    if (~p2) assert(gcd(p1 + p2, i) == 1);
  }
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);

  sieve();
  int tt = 1;
  //cin >> tt;
  FOR (t, 1, tt + 1) {
      // cout << "Case #" << t << ": ";
      solve();
  }

  return 0;
}
