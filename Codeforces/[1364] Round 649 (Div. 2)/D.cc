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

vi parent, height;
ii best{-1, -1};
vvi adj;

void dfs (int v = 0, int h = 0, int p = -1) {
  height[v] = h;
  parent[v] = p;
  for (int u : adj[v]) {
    if (height[u] == -1) dfs(u, h + 1, v);
    else if (height[u] + 1 < height[v]){
      int cyclen = height[v] - height[u] + 1;
      if (best.fi == -1 || best.fi > cyclen) {
        best = mp(cyclen, v);
      }
    }
  }
}

void solve() {
  int n, m, k;
  cin >> n >> m >> k;
  adj.resize(n);
  parent.assign(n, -1); height.assign(n, -1);
  F0R (_, m) {
    int a, b;
    cin >> a >> b;
    --a; --b;
    adj[a].pb(b);
    adj[b].pb(a);
  }
  dfs();
  dout << dvar(parent) << endl;
  dout << dvar(height) << endl;
  dout << dvar(best) << endl;
  if (best.fi == -1) {
    vi odd, even;
    F0R (i, n) {
      if (height[i] & 1) {
        odd.pb(i + 1);
      } else {
        even.pb(i + 1);
      }
    }
    cout << 1 << endl;
    k = (k + 1) / 2;
    if (SZ(even) >= k) {
      F0R (i, k) cout << even[i] << ' ';
    } else {
      F0R (i, k) cout << odd[i] << ' ';
    }
  } else if (best.fi <= k) {
    cout << 2 << endl;
    cout << best.fi << endl;
    int iter = best.se;
    F0R (_, best.fi) {
      cout << iter + 1 << ' ';
      iter = parent[iter];
    }
  } else {
    cout << 1 << endl;
    k = (k + 1) / 2;
    int iter = best.se;
    F0R (_, k) {
      cout << iter + 1 << ' ';
      F0R (i, 2) {
        if (~iter) {
          iter = parent[iter];
        }
      }
    }
  }
  cout << endl;
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
