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

ll gauss(ll n) {
  return (n + 1) * n / 2;
}

struct up {
  bool assign_p = 0;
  ll assign = 0, add = 0;
  int left = 0, right = 0;
  up getLeft(int k) {
    up res = *this;
    res.add += k * right;
    return res;
  }
  up getRight(int k) {
    up res = *this;
    res.add += k * left;
    return res;
  }
  up fromLeft(int len, int idx, int k) {
    up res = *this;
    if (left) {
      res.add = idx;
    } else if (right) {
      res.add = len - (idx + k);
    }
    return res;
  }
  up fromRight(int len, int idx, int k) {
    up res = *this;
    if (right) {
      res.add = idx;
    } else if (left) {
      res.add = len - (idx + k); 
    }
    return res;
  }
};
ostream& operator<<(ostream& o, const up& u) {
  return o << dvar(u.assign_p, u.assign, u.add, u.left, u.right);
}


struct ST {
  using T = ll;
  const T unit = 0;
  T merge(T l, T r) { return l + r; };
  int n, h;
  vector<T> data;
  vector<up> delay;
  ST(int n) : n(n), h(32 - __builtin_clz(n)), data(2 * n), delay(n) {}
  void build() {
    for (int i = n - 1; i > 0; --i)
      data[i] = merge(data[i << 1], data[i << 1 | 1]);
  }
  void calc(int p, int k, up& u) {
    if (u.assign_p) data[p] = k * u.assign;
    data[p] += u.add * k + (u.left + u.right) * gauss(k);
  }
  void apply(int p, int k, up u) {
    calc(p, k, u);
    if (p < n) {
      if (u.assign_p) {
        delay[p] = u;
      } else {
        delay[p].left += u.left; delay[p].right += u.right;
        delay[p].add += u.add;
      }
    }
  }
  void upPar(int p) {
    for (int k = 2; p > 1; k <<= 1) {
      p >>= 1;
      data[p] = merge(data[p << 1], data[p << 1 | 1]);
      calc(p, k, delay[p]);
    }
  }
  void push(int p) {
    for (int s = h, k = 1 << (h - 1); s; --s, k >>= 1) {
      int i = p >> s;
      apply(i << 1, k, delay[i].getLeft(k));
      apply(i << 1 | 1, k, delay[i].getRight(k));
      delay[i] = up{};
    }
  }
  T query(int l, int r) {
    T li = unit, ri = unit;
    l += n; r += n;
    push(l); push(r - 1);
    for (; l < r; r >>= 1, l >>= 1) {
      if (l & 1) li = merge(li, data[l++]);
      if (r & 1) ri = merge(data[--r], ri);
    }
    return merge(li, ri);
  }
  void update(int l, int r, up u) {
    dout << "up: " << u << endl;
    l += n; r += n;
    int l0 = l, r0 = r;
    push(l); push(r - 1);
    p();
    up ul = u, ur = u;
    if (u.left) {
      ur.add = r - l - 1;
    } else if (u.right) {
      ul.add = r - l - 1;
    }
    int lidx = 0, ridx = 0;
    for (int k = 1; l < r; l >>= 1, r >>= 1, k <<= 1) {
      if (l & 1) {
        apply(l++, k, u.fromLeft(r0 - l0, lidx, k));
        lidx += k;
      }
      if (r & 1) {
        apply(--r, k, u.fromRight(r0 - l0, ridx, k));
        ridx += k;
      }
    }
    p();
    upPar(l0); upPar(r0 - 1);
  }

  void assign(int l, int r, T val) {
    up u;
    u.assign_p = 1; u.assign = val;
    update(l, r, u);
  }
  void add(int l, int r, bool left) {
    up u;
    u.left = left; u.right = !left;
    update(l, r, u);
  }
  void p() {
    if (!DEBUG) return;
    dout << dvar(data) << endl;
    for (auto& u : delay) dout << u << endl;
    dout << endl;
  }
};
 

int main() {
  ios_base::sync_with_stdio(0);
  cout.tie(0);

  ST st(250000);
  int q;
  cin >> q;
  while (q--) {
    char t;
    int l, r;
    cin >> t >> l >> r;
    --l;
    dout << dvar(st.data) << endl;
    for (auto& u : st.delay) dout << u << endl;
    dout << endl;


    if (t == 'S') {
      cout << st.query(l, r) << endl;
    }
    else if (t == 'C') {
      int x;
      cin >> x;
      st.assign(l, r, x);
    } else {
      st.add(l, r, t == 'A');
    }
  }
  
  return 0;
}
