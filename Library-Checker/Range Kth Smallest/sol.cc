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

struct BV {
  struct BLK {
    using T = uint32_t;
    T bits = 0;
    int sum = 0;
    static constexpr int sz = sizeof(T) * 8;
    int rank() { return __builtin_popcount(bits); }
    int rank(int i) {
      return __builtin_popcount(bits & ((T)1 << i) - (T)1);
    }
  };
  vector<BLK> data;
  void resize(int n) { data.resize((n + BLK::sz - 1) / BLK::sz); }
  int rank1(int idx) {
    int i = idx / BLK::sz;
    if (i == 0) return data[0].rank(idx);
    return data[i - 1].sum + data[i].rank(idx % BLK::sz);
  }
  int rank0(int idx) {
    return idx - rank1(idx);
  }
  void set(int i) {
    data[i / BLK::sz].bits |= (BLK::T)(1) << (i % BLK::sz);
  }
  int get(int i) {
    return data[i / BLK::sz].bits >> (i % BLK::sz) & 1; 
  }
  void build() {
    F0R (i, SZ(data)) {
      data[i].sum = data[i].rank();
      if (i) data[i].sum += data[i - 1].sum;
    }
  }
};

template<typename T = int>
struct WLM {
  static inline int cld(uint64_t i) { return 64 - __builtin_clzll(i); }
  static inline int bit(T n, int i) { return n >> i & 1; }
  T H;
  vector<BV> bvs;
  vi zs;
  WLM(vector<T> v, T hi) : H{cld(hi)}, bvs(H), zs(H) {
    int n = SZ(v);
    for (int h = H - 1; ~h; --h) {
      bvs[h].resize(n);
      F0R (i, n) if (bit(v[i], h)) bvs[h].set(i); 
      bvs[h].build();
      zs[h] = distance(v.begin(),
                       stable_partition(ALL(v), [=](T i){ return !bit(i, h); }));
    }
  }
  // k-th smallest in [l, r)
  T kthsmallest(int l, int r, int k) {
    T lo = 0, hi = (T)1 << H;
    for (int h = H - 1; ~h; --h) {
      int have = bvs[h].rank0(r) - bvs[h].rank0(l);
      if (k < have) {
        hi -= (T)1 << h;
        l = bvs[h].rank0(l); r = bvs[h].rank0(r);
      } else {
        lo += (T)1 << h; k -= have;
        l = zs[h] + bvs[h].rank1(l); r = zs[h] + bvs[h].rank1(r);
      }
    }
    return lo;
  }
};

int main() {
  ios_base::sync_with_stdio(0);
  cout.tie(0); cin.tie(0);

  int n, q; cin >> n >> q;
  vi as(n); F0R (i, n) cin >> as[i];
  WLM wlm(move(as), (int)1e9 + 1);
  while (q--) {
    int l, r, k; cin >> l >> r >> k;
    cout << wlm.kthsmallest(l, r, k) << endl;
  }
  
  return 0;
}
