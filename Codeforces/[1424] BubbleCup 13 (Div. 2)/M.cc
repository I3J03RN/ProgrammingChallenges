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
#define eb emplace_back
#define pb push_back
#define mp make_pair
#define mt make_tuple
#define endl '\n'
#define ALL(x) (x).begin(), (x).end()
#define RALL(x) (x).rbegin(), (x).rend()
#define SZ(x) (int)(x).size()
#define FOR(a, b, c) for (auto a = (b); (a) < (c); ++(a))
#define F0R(a, b) FOR (a, 0, (b))
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
#define dout if (DEBUG) cerr
#define dvar(...) " \x1b[35m[" << #__VA_ARGS__ ": " << mt(__VA_ARGS__) << "]\x1b[0m "
template <typename T>
true_type const_iterator_check(typename T::const_iterator*);
template <typename T>
false_type const_iterator_check(...);
template <typename T>
struct IsC : decltype(const_iterator_check<T>(nullptr)) {};
template <>
struct IsC<string> : false_type {};
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

int main() {
  ios_base::sync_with_stdio(0);
  cout.tie(0); cin.tie(0);

  int n, k; cin >> n >> k;
  vector<string> s(n * k);
  vector<bool> found(27);
  found[26] = true;
  F0R (i, n) {
    int p; cin >> p;
    F0R (j, k) {
      cin >> s[p * k + j];
      for (char c : s[p * k + j]) found[c - 'a'] = true;
      s[p * k + j] += char('z' + 1);
    }
  }
  vector<vector<bool>> adj(27, vector(27, false));
  F0R (i, SZ(s) - 1) {
    F0R (j, min(SZ(s[i]), SZ(s[i + 1]))) {
      if (s[i][j] != s[i + 1][j]) {
        adj[s[i][j] - 'a'][s[i + 1][j] - 'a'] = true;
        break;
      }
    }
  }

  F0R (i, 26) {
    if (adj[i][26]) {
      cout << "IMPOSSIBLE" << endl;
      return 0;
    }
  }

  tprint(adj, 3);

  vi in(27);
  F0R (i, 27) {
    F0R (j, 27) {
      in[j] += !!adj[i][j];
    }
  }
  
  vi t; 
  F0R (i, 27) {
    if (found[i] && in[i] == 0) {
      t.pb(i);
    }
  }
  F0R (i, SZ(t)) {
    F0R (j, 27) {
      if (adj[t[i]][j]) {
        if (--in[j] == 0) {
          t.pb(j);
        }
      }
    }
  }
  if (SZ(t) != count(ALL(found), true)) {
    cout << "IMPOSSIBLE" << endl;
  } else {
    F0R (i, SZ(t)) if (t[i] < 26) cout << char('a' + t[i]);
    cout << endl;
  }
  
  return 0;
}
