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
#define eb emplace_back
#define pb push_back
#define mp make_pair
#define mt make_tuple
#define SZ(x) (int)(x).size()
// #define endl '\n'
#define FOR(a, b, c) for (auto a = (b); (a) < (c); ++(a))
#define F0R(a, b) FOR (a, 0, (b))
#define CEIL(a, b) ((a) + (b)-1) / (b)
template <class T>
bool ckmin(T& a, const T& b) {
  return a > b ? a = b, true : false;
}
template <class T>
bool ckmax(T& a, const T& b) {
  return a < b ? a = b, true : false;
}
#ifndef DEBUG
#define DEBUG 0
#endif
#define dout \
  if (DEBUG) std::cerr
#define dvar(...) " [" << #__VA_ARGS__ ": " << mt(__VA_ARGS__) << "] "
template <typename T>
struct IsC {
  template <typename C>
  static char test(typename C::const_iterator*);
  template <typename C>
  static int test(...);
  static const bool value = sizeof(test<T>(0)) == sizeof(char);
};
template <>
struct IsC<string> {
  static const bool value = false;
};
template <typename C>
typename enable_if<IsC<C>::value, ostream&>::type operator<<(ostream&, const C&);
template <typename T1, typename T2>
ostream& operator<<(ostream&, const pair<T1, T2>&);
template <typename... T> using TS = tuple_size<tuple<T...>>;
template<size_t idx, typename... T>
typename enable_if<TS<T...>::value == idx + 1, ostream&>::type
operator<<(ostream& o, const tuple<T...>& t) {
  return o << ", " << get<idx>(t) << ')';
}
template<size_t idx, typename... T>
typename enable_if<0 < idx && idx + 1 < TS<T...>::value, ostream&>::type
operator<<(ostream& o, const tuple<T...>& t) {
  return operator<<<idx + 1>(o << ", " << get<idx>(t), t);
}
template<size_t idx = 0, typename... T>
typename enable_if<1 < TS<T...>::value && !idx, ostream&>::type
operator<<(ostream& o, const tuple<T...>& t) {
  return operator<<<idx + 1>(o << '(' << get<idx>(t), t);
}
template<typename T>
ostream& operator<<(ostream& o, const tuple<T>& t) {
  return o << get<0>(t);
}
template <typename T1, typename T2>
ostream& operator<<(ostream& o, const pair<T1, T2>& p) {
  return o << mt(p.fi, p.se);
}
template <typename C>
typename enable_if<IsC<C>::value, ostream&>::type operator<<(
    ostream& o, const C& c) {
  o << '[';
  for (auto it = c.cbegin(); it != c.cend(); ++it)
    o << *it << (next(it) != c.cend() ? ", " : "");
  return o << ']';
}
template <typename T>
void tprint(vector<vector<T>>& v, size_t width = 0, ostream& o = cerr) {
  if (!DEBUG) return;
  for (const auto& vv : v) {
    for (const auto& i : vv) o << setw(width) << i;
    o << endl;
  }
}
const int N = 5e4;
int lp[N + 1];
vi pr;
void sieve() {
  FOR (i, 2, N + 1) {
    if (!lp[i]) {
      lp[i] = i;
      pr.pb(i);
    }
    for (int j = 0; j < SZ(pr) && pr[j] <= lp[i] && i * pr[j] <= N; ++j)
      lp[i * pr[j]] = pr[j];
  }
}

bool isPrime(int n) {
  if (n < N) return lp[n] == n;
  for (int i = 2; i * i <= n; ++i) {
    if (n % i == 0) {
      return false;
    }
  }
  return true;
}

void solve() {
  int n; cin >> n;
  vii pdivs;
  vi divs;
  for (int i = 0, nn = n; i < SZ(pr) || nn > 1; ++i) {
    if (i == SZ(pr)) {
      pdivs.eb(nn, 1);
      break;
    }
    int cnt = 0;
    for (; nn % pr[i] == 0; nn /= pr[i]) {
      ++cnt;
    }
    if (cnt) {
      pdivs.eb(pr[i], cnt);
    }
  }
  if (SZ(pdivs) == 2 && pdivs[0].se == 1 && pdivs[1].se == 1) {
    cout << n << ' ' << pdivs[0].fi << ' ' << pdivs[1].fi << endl;
    cout << 1 << endl;
    return;
  }
  vvi ex(SZ(pdivs));
  vi skiped;
  for (vi idx(SZ(pdivs), 0);;) {
    ++idx.back();
    for (int j = SZ(pdivs) - 1; j > 0 && idx[j] > pdivs[j].se; --j) {
      idx[j] = 0;
      ++idx[j - 1];
    }
    if (idx[0] > pdivs[0].se) {
      break;
    }
    int val = 1;
    int last = -1;
    int cnt = 0;
    F0R (j, SZ(pdivs)) {
      if (idx[j]) {
        last = j; 
        ++cnt;
      }
      F0R (_, idx[j]) {
        val *= pdivs[j].fi;
      }
    }
    if (cnt == 2 && (pdivs[last].fi * pdivs[last - 1].fi == val || pdivs[last].fi * pdivs[(last + 1) % SZ(pdivs)].fi == val)) {
      skiped.pb(val);
    } else {
      ex[last].pb(val);
    }
  }
  if (SZ(ex) == 1) {
    for (int i : ex[0]) {
      cout << i << ' ';
    }
  } else if (SZ(ex) == 2) {
    for (int i : ex[0]) {
      cout << i  << ' ';
    }
    cout << ex[0][0] * ex[1][0] << ' ';
    for (int i : ex[1]) {
      cout << i << ' ';
    }
  } else {
    F0R (i, SZ(ex)) {
      for (int j : ex[i]) {
        cout << j << ' ';
      }
      cout << ex[i][0] * ex[(i + 1) % SZ(ex)][0] << ' ';
    }
  }
  cout << endl << 0 << endl;
}

int main() {
  ios_base::sync_with_stdio(0);
  cout.tie(0); cin.tie(0);
  sieve();

  int tt = 1;
  cin >> tt;
  FOR (t, 1, tt + 1) {
    // cout << "Case #" << t << ": ";
    solve();
  }
  
  return 0;
}
