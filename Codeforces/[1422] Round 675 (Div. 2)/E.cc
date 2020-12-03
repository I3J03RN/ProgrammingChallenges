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
#define dvar(...) " [" << #__VA_ARGS__ ": " << mt(__VA_ARGS__) << "] "
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

  string s; cin >> s;
  int n = SZ(s);
  s += char('a' - 1);
  vector<char> nxtD(n + 1);
  vector<string> last(n + 1);
  nxtD[n - 1] = nxtD[n] = 'a' - 1;
  vi dp(n + 1);
  vi ptr(n + 1);
  dp[n - 1] = 1;
  ptr[n - 1] = n - 1;
  last[n - 1] = s[n - 1];
  ptr[n] = n;
  for (int i = n - 2; ~i; --i) {
    if (s[i] == s[i + 1]) {
      if (s[i] < s[ptr[i + 2]] ) { // take
        dp[i] = dp[i + 2] + 2;
        nxtD[i] = s[ptr[i + 2]];
        ptr[i] = i;
        if (SZ(last[i + 2]) == 2) {
          last[i] = last[i + 2];
        } else {
          string t = s.substr(i, 2) + last[i + 2];
          last[i] = t.substr(SZ(t) - 2, 2);
        }
      } else if (s[i] == s[ptr[i + 2]] && nxtD[i + 2] > s[i]) { // take
        dp[i] = dp[i + 2] + 2;
        nxtD[i] = nxtD[i + 2];
        ptr[i] = i;
        if (SZ(last[i + 2]) == 2) {
          last[i] = last[i + 2];
        } else {
          string t = s.substr(i, 2) + last[i + 2];
          last[i] = t.substr(SZ(t) - 2, 2);
        }
      } else { // don't take
        dp[i] = dp[i + 2];
        last[i] = last[i + 2];
        nxtD[i] = nxtD[i + 2];
        ptr[i] = ptr[i + 2];
      }
    } else {
      dp[i] = dp[i + 1] + 1;
      if (SZ(last[i + 1]) == 2) {
        last[i] = last[i + 1];
      } else {
        string t = s[i] + last[i + 1];
        last[i] = t.substr(max(0, SZ(t) - 2), 2);
      }
      if (s[i] == s[ptr[i + 1]]) {
        nxtD[i] = nxtD[i + 1];
      } else {
        nxtD[i] = s[ptr[i + 1]];
      }
      ptr[i] = i;
    }
  }
  dout << dvar(dp) << endl;
  dout << dvar(nxtD) << endl;
  dout << dvar(ptr) << endl;
  dout << dvar(last) << endl;

  F0R (i, n) {
    cout << dp[i] << ' ';
    if (dp[i] > 10) {
      for (int j = i, k = 0; k < 5; ++k, j = ptr[j] + 1) {
        cout << s[ptr[j]];
      }
      cout << "..." << last[i];
    } else {
      for (int j = i; ptr[j] < n; j = ptr[j] + 1) {
        cout << s[ptr[j]];
      }
    }
    cout << endl;
  }
  
  return 0;
}
