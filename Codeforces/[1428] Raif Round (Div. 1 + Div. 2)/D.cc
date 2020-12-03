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
template <typename C>
typename enable_if<IsC<C>::value, istream&>::type operator>>(istream& i, C& v) {
  for (auto& x : v) i >> x;
  return i;
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
  cin.tie(0);

  int n; cin >> n;
  vi as(n); cin >> as;

  vi ones, more;
  F0R (i, n) {
    if (as[i] == 1) ones.pb(i);
    if (as[i] >= 2) more.pb(i);
  }

  vii sol;
  int top = 0;
  int o = 0, m = 0;
  vi row(n, -1);
  F0R (i, n) {
    if (o < SZ(ones) && ones[o] == i) ++o;
    if (m < SZ(more) && more[m] == i) ++m;
    if (as[i] == 0) continue;
    if (as[i] == 1) {
      if (row[i] == -1) {
        row[i] = top++;
      }
      sol.eb(row[i], i);
    }
    if (as[i] == 2) {
      if (o == SZ(ones)) {
        cout << -1 << endl;
        return 0;
      }
      if (row[i] == -1) {
        sol.eb(row[i] = top++, i);
      }
      row[ones[o++]] = row[i];
    }
    if (as[i] == 3) {
      if (m == SZ(more)) {
        if (o == SZ(ones)) {
          cout << -1 << endl;
          return 0;
        }
        row[i] = top++;
        sol.eb(row[i], i); sol.eb(row[i], ones[o++]);
      } else {
        row[i] = top++; 
        sol.eb(row[i], i); sol.eb(row[i], more[m++]);
      }
    }
  }

  assert(SZ(sol) <= 2 * n);
  cout << SZ(sol) << endl;
  for (auto [r, c] : sol) cout << r + 1 << ' ' << c + 1 << endl;
  
  return 0;
}
