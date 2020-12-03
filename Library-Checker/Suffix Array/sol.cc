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

vii SA_ns, SA_bs;
using vit = vi::iterator;
template<int B = 'a', int S = 26, int N = 3>
struct SA {
  vi sa;
  SA(const string& s) {
    SA_bs.resize(max(S, SZ(s)) + 2);
    SA_ns.resize(max(S, SZ(s)) + 2);
    vi ra(SZ(s) + 1 + N);
    F0R (i, SZ(s)) ra[i] = s[i] - B + 2;
    ra[SZ(s)] = 1;
    sa = build(ra);
  }
  vi build(const vi& prefRank) {
    int n = SZ(prefRank) - N;
    int offset = n / N + !!(n % N);
    vi arr; arr.reserve(n);
    array<int, N> offs;
    F0R (j, N) {
      offs[j] = SZ(arr) - offset;
      for (int i = j; i < n; i += N) arr.pb(i);
    }
    rsort(offset + ALL(arr), N, [&](int i, int it) { return prefRank[i + it]; });
    vi ra(n - offset + N);
    int r = 1;
    FOR (i, offset, n) {
      ra[offs[arr[i] % N] + arr[i] / N] = r;
      if (i + 1 < n)
        F0R (j, N)
          if (prefRank[arr[i] + j] != prefRank[arr[i + 1] + j]) {
            r++; break;
          }
    }
    if (r < n - offset) {
      vi got(build(ra));
      F0R (i, SZ(got)) ra[got[i]] = i;
      FOR (j, 1, N) for (int i = 0; j + i * N < n; ++i)
        arr[offset + ra[offs[j] + i]] = j + i * N;
    }
    rsort(arr.begin(), arr.begin() + offset, 2, [&](int i, int it) {
      return it ? ra[offs[(i + 1) % N] + (i + 1) / N] : prefRank[i];
    });
    vi tmp(arr.begin(), arr.begin() + offset);
    int o = 0, m = offset, i = 0;
    while (o < offset && m < n) {
      int c = 0;
      for (int k = 0; !c; ++k) {
        int a = tmp[o] + k, b = arr[m] + k;
        c = (a % N && b % N) 
          ? cmp(ra[offs[a % N] + a / N], ra[offs[b % N] + b / N]) 
            : cmp(prefRank[a], prefRank[b]);
      }
      arr[i++] = c < 0 ? tmp[o++] : arr[m++];
    }
    while (o < offset) arr[i++] = tmp[o++];
    return arr;
  }
  static inline int cmp(int a, int b) { return (a > b) - (a < b); }
  template<typename F>
  static void rsort(vit vb, vit ve, int iters, F bf) {
    for (int d = iters - 1; ~d; --d) {
      int mx = 0;
      F0R (i, distance(vb, ve)) {
        int b = bf(*(vb + i), d);
        for (; mx <= b; ++mx) SA_bs[mx].fi = -1;
        if (SA_bs[b].fi == -1) SA_bs[b] = mp(i, i);
        SA_ns[SA_bs[b].se].se = i;
        SA_ns[i] = mp(*(vb + i), -1);
        SA_bs[b].se = i;
      }
      vit j = vb;
      F0R (i, mx)
        for (int it = SA_bs[i].fi; ~it; it = SA_ns[it].se, ++j)
          *j = SA_ns[it].fi;
    }
  }
};

int main() {
  cin.tie(0); cout.tie(0);
  ios_base::sync_with_stdio(false);

  string s; cin >> s;
  dout << dvar(s) << endl;
  SA sa(s);
  FOR (i, 1, SZ(sa.sa)) cout << sa.sa[i] << ' ';
  cout << endl;
  
  return 0;
}
