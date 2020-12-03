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

template<typename T>
int cmp(T a, T b) {
  if (a < b) return -1;
  if (a > b) return 1;
  return 0;
}

template<typename T>
T getOr(const vector<T>& v, const int idx, T alternative) {
  return 0 <= idx && idx < SZ(v) ? v[idx] : alternative;
}

template<int N>
vi sa(const vi& pref) {
  dout << dvar(pref) << endl;
  array<vi, N> vs{};
  F0R (i, SZ(pref)) {
    vs[i % N].pb(i);
  }
  dout << dvar(vs) << endl;
  vi more; more.reserve(SZ(pref) - SZ(vs[0]));
  FOR (i, 1, N) {
    more.insert(more.end(), ALL(vs[i]));
  }
  dout << dvar(more) << endl;
  vi pos(SZ(pref), -1); 
  F0R (i, SZ(more)) {
    pos[more[i]] = i;
  }
  sort(ALL(more), [&](int a, int b) {
    int c = 0;
    for (int i = 0; i < N && !c; ++i) {
      c = cmp(getOr(pref, a + i, -1), getOr(pref, b + i, -1));
    }
    return c < 0;
  });
  dout << dvar(more) << endl;
  dout << dvar(pos) << endl;
  vi ra(SZ(more));
  bool rec = false;
  for (int r = 0, i = 0; i < SZ(more); ++i) {
    ra[pos[more[i]]] = r;
    if (i + 1 < SZ(more)) {
      bool inc = false;
      F0R (j, N) {
        if (getOr(pref, more[i] + j, -1) != getOr(pref, more[i + 1] + j, -1)) {
          inc = true; break;
        }
      }
      if (inc) {
        ++r;
      } else {
        rec = true;
      }
    }
  }
  dout << dvar(ra) << endl;
  if (rec) {
    vi got = sa<N>(ra);
    F0R (i, SZ(got)) {
      ra[got[i]] = i;
    }
    F0R (i, SZ(pos)) {
      if (~pos[i]) {
        more[ra[pos[i]]] = i;
      }
    }
    dout << "after rec: " << dvar(more) << endl;
  }
  dout << dvar(ra) << endl;
  vi& one = vs[0];
  sort(ALL(one), [&](int a, int b) {
    return mp(pref[a], getOr(ra, getOr(pos, a + 1, -1), -1)) < mp(pref[b], getOr(ra, getOr(pos, b + 1, -1), -1));
  });
  dout << dvar(one) << endl;
  vi res; res.reserve(SZ(pref));
  for (int o = 0, m = 0; o < SZ(one) || m < SZ(more);) {
    if (o == SZ(one))  {
      res.pb(more[m++]);
    } else if (m == SZ(more)) {
      res.pb(one[o++]);
    } else {
      int c = 0;
      for (int k = 0; !c; ++k) {
        int a = one[o] + k, b = more[m] + k;
        if (a % N == 0 || b % N == 0) {
          c = cmp(getOr(pref, a, -1), getOr(pref, b, -1));
        } else {
          c = cmp(getOr(ra, getOr(pos, a, -1), -1), getOr(ra, getOr(pos, b, -1), -1));
        }
      }
      if (c < 0) {
        res.pb(one[o++]);
      } else {
        res.pb(more[m++]);
      }
    }
  }
  dout << dvar(res) << endl;
  return res;
}

template<int B = 'a', int N = 3>
vi sa(string s) {
  vi v(SZ(s) + 1);
  iota(ALL(v), 0);
  vi ra(SZ(s) + 1);
  F0R (i, SZ(s)) {
    ra[i] = s[i] - B + 1;
  }
  ra[SZ(s)] = 0;
  return sa<N>(ra);
}

vi sa_stupid(const string& s) {
  vector<pair<string, int>> v;
  F0R (i, SZ(s) + 1) {
    v.eb(s.substr(i), i);
  }
  sort(ALL(v));
  vi vv(SZ(v)); 
  F0R (i, SZ(v)) {
    vv[i] = v[i].se;
  }
  return vv;
}

int main() {
  ios_base::sync_with_stdio(0);
  cout.tie(0); cin.tie(0);

  string s; cin >> s;
  vi arr = sa(s);
  FOR (i, 1, SZ(arr)) cout << arr[i] << ' ';
  cout << endl;
  
  return 0;
}
