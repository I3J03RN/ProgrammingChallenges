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
#define endl '\n'
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
  for (auto& vv : v) {
    for (auto& i : vv) o << setw(width) << i;
    o << endl;
  }
}

struct node {
  bool lin = 0, rin = 0;
  int l = 0, r = 0, mid = -1;
  bool full = 0;
};

void p(node& a) {
  if (!DEBUG) return;
  dout << dvar(a.lin, a.rin, a.l, a.r, a.mid, a.full) << endl;;
}

struct ST;
// <<>><<>> >><<>><<
// <<<<<<<  <<<<<<<<  ||| <<<<>>>> >><<>>>> ||| >><< <<<<
struct ST {
  using T = node;
  const T unit{};
  T merge(T l, T r) {
    if (l.mid == -1) return r;
    if (r.mid == -1) return l;
    if (l.full && r.full) {
      if (l.rin && r.lin) {
        // >< >< not full! ><><
        return {l.lin, r.rin, l.l, r.r, 0, 0};
      } else {
        return{l.lin, r.rin, l.l + r.r, l.l + r.r, 0, 1}; 
      }
    } else {
      if (r.full && r.rin && !r.lin && l.rin) {
        return {l.lin, r.rin, l.l, l.r + r.r, l.mid, 0};
      } else if (l.full && l.lin && !l.rin && r.lin) {
        return {l.lin, r.rin, l.l + r.l, r.r, r.mid, 0};
      } else { 
        return {l.lin, r.rin, l.l, r.r,
                max({l.mid, r.mid, (l.rin && r.lin) ? max(l.r, r.l) : l.r + r.l}), 0};
        // >>> <<< ||| <<< >>> || <<< <<< || >>> >>>
      }
    }
  };
  int n, h;
  vector<vector<T>> data;
  vector<bool> flip, idx;
  ST(int n) : n(n), h(32 - __builtin_clz(n)), data(2, vector<T>(2 * n)), flip(n), idx(2 * n, 0) {}
  void apply(int p) {
    idx[p] = !idx[p];
    if (p < n) flip[p] = !flip[p];
  }
  void build() {
    for (int i = n - 1; i > 0; --i) {
    F0R (j, 2) 
      data[j][i] = merge(data[j][i << 1], data[j][i << 1 | 1]);
    }
  }
  T query(int l, int r) {
    T li = unit, ri = unit;
    l += n, r += n;
    push(l); push(r - 1);
    for (; l < r; r >>= 1, l >>= 1) {
      if (l & 1) {
        li = merge(li, data[idx[l]][l]);
        l++;
        // dout << dvar(l - 1);
        // p(li);
      }
      if (r & 1) {
        --r;
        ri = merge(data[idx[r]][r], ri);
        // dout << dvar(r);
        // p(ri);
      }
    }
    return merge(li, ri);
  }
  void upPar(int p) {
    while (p > 1) {
      p >>= 1;
      F0R (j, 2) data[j][p] = merge(data[j][p << 1], data[j][p << 1 | 1]);
      if (flip[p]) idx[p] = !idx[p];
    }
  }
  void push(int p) {
    for (int s = h; s > 0; --s) {
      int i = p >> s;
      if (flip[i]) {
        apply(i << 1);
        apply(i << 1 | 1);
        flip[i] = 0;
      }
    }
  }
  void update(int l, int r) {
    l += n; r += n;
    int l0 = l, r0 = r;
    for (; l < r; l >>= 1, r >>= 1) {
      if (l & 1) apply(l++);
      if (r & 1) apply(--r);
    }
    upPar(l0); upPar(r0 - 1);
  }
};

// void p2(ST& st) {
//   if (!DEBUG) return;
//   F0R (i, st.n << 1) {
//     dout << dvar(i);
//     p(st.data[i]);
//     dout << dvar(i);
//     p(st.swapdata[i]);
//     dout << endl;
//   }
//   dout << dvar(st.flip);
//   dout << endl;
// }

int main() {
  ios_base::sync_with_stdio(0);
  cout.tie(0);

  int n, q;
  cin >> n >> q;
  string s;
  cin >> s;
  ST st(n);
  F0R (i, n) {
    st.data[s[i] == '>'][i + n] = {0, 1, 1, 1, 0, 1};
    st.data[s[i] == '<'][i + n] = {1, 0, 1, 1, 0, 1};
  }
  st.build();
  while (q--) {
    int l, r;
    cin >> l >> r;
    --l;
    FOR (i, l, r) {
      if (s[i] == '<') s[i] = '>';
      else s[i] = '<';
    }
    // int best = 0;
    // int lst = 0, cnt = 0;
    // FOR (i, l, r) {
    //   if (s[i] == '<') {
    //     // before >
    //     if (lst == 0) {
    //       lst = cnt; cnt = 0;
    //     }
    //     lst++;
    //   } else { // >
    //     // before <
    //     ckmax(best, lst);
    //     lst = 0;
    //     cnt++;
    //   }
    // }
    // ckmax(best, max(lst, cnt));
    // p2(st);
    // cout << "b: " << best << endl;
  
    st.update(l, r);
    node a = st.query(l, r);
    // dout << "qres :";           
    // p(a);
    cout << max({a.l, a.r, a.mid}) << endl;
    // p(a);
    // dout << endl;
  }
  // p2(st);
  
  return 0;
}
