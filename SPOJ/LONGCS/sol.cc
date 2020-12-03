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
  vi sa, rank, lcp;
  SA(const string& s) {
    SA_bs.resize(max(S, SZ(s)) + 2);
    SA_ns.resize(max(S, SZ(s)) + 2);
    vi ra(SZ(s) + 1 + N);
    F0R (i, SZ(s)) ra[i] = s[i] - B + 2;
    ra[SZ(s)] = 1;
    sa = build(ra);
  }
  void buildRank() {
    rank.resize(SZ(sa));
    F0R (i, SZ(sa)) rank[sa[i]] = i;
  }
  void buildLcp(const string& s) {
    if(rank.empty()) buildRank();
    lcp.resize(SZ(sa) - 1);
    int k = 0;
    F0R (i, SZ(sa)) {
      if (rank[i] == SZ(sa) - 1) {
        k = 0; continue;
      }
      for (int j = sa[rank[i] + 1]; max(i, j) + k < SZ(s) && s[i + k] == s[j + k]; ++k);
      lcp[rank[i]] = k;
      if (k) --k;
    }
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

struct SPT {
  vvi spT, idx; // min value, pos of min value
  SPT(vi& A) {
    const int logn = 33 - __builtin_clz(SZ(A));
    spT.assign(SZ(A), vi(logn));
    idx.assign(SZ(A), vi(logn));
    F0R (i, SZ(A)) spT[i][0] = A[i], idx[i][0] = i;
    for (int j = 1; (1 << j) <= SZ(A); ++j)
      for (int i = 0; i + (1 << j) <= SZ(A); ++i) {
        int k = i + (1 << (j - 1));
        spT[i][j] = spT[k][j - 1], idx[i][j] = idx[k][j - 1];
        if (ckmin(spT[i][j], spT[i][j - 1])) idx[i][j] = idx[i][j - 1];
    }
  }
  ii rmq(int l, int r) {
    int k = 31 - __builtin_clz(r - l + 1);
    return min(mp(spT[l][k], idx[l][k]),
               mp(spT[r - (1 << k) + 1][k], idx[r - (1 << k) + 1][k]));
  }
};


void solve() {
  int k; cin >> k;
  if (k == 1) {
    string sss; cin >> sss;
    cout << SZ(sss) << endl;
    return;
  }
  vector<string> ss(k); F0R (i, k) cin >> ss[i];
  string s = ss[0];
  vi until(k, SZ(s));
  FOR (i, 1, k) {
    s += string(1, '#' + i - 1) + ss[i];
    until[i] = SZ(s);
  }
  SA<'#', 128> sa(s);
  sa.buildLcp(s);
  SPT st(sa.lcp);
  int good = 0, best = 0;
  vi cnt(k);
  int l = k, r = k - 1;
  while (true) {
    if (good == k) {
      ckmax(best, st.rmq(l, r - 1).fi);
      int u = 0;
      while (sa.sa[l] >= until[u]) ++u;
      if (--cnt[u] == 0) --good;
      l++;
    } else {
      ++r;
      if (r == SZ(sa.sa)) break;
      int u = 0;
      while (sa.sa[r] >= until[u]) ++u;
      if (cnt[u]++ == 0) ++good;
    }
  }
  cout << best << endl;
}

int main() {
  ios_base::sync_with_stdio(0);
  cout.tie(0); cin.tie(0);

  int tt; cin >> tt;
  while (tt--) solve(); 
  
  return 0;
}
