///////////////////////////////////////////////////////////////
// Long template from: https://github.com/Zeldacrafter/CompProg
//
// Feature list:
// * C++14 compatibility.
// * Various 'define'-shorthands and typedefs.
// * Output stream that is only active with 'DEBUG'-flag set.
// * Input and output stream operators for...
//   * any container with 'begin' and 'end' iterator.
//   * tuples with any amount of elements
//     (Except for 0 elements tuples :'( ) Related: https://xkcd.com/541/
//   * pairs.
// * PrettyPrinting a object with specified seperators.
//   Each additional seperator specifies the seperator for one level
//   further into a nested structure. Pairs, tuples and std-library-container
//   cause the level to increase.
//   If no seperator is specified a default of " "(space) is used.
//   For example a call
//      vii a(4, mp(1, 2));
//      cout << pp(a, " | ", "-");
//   results in the output (without trailing newline)
//      1-2 | 1-2 | 1-2 | 1-2
///////////////////////////////////////////////////////////////

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
template <typename T>
bool ckmin(T& a, const T& b) { return a > b ? a = b, true : false; }
template <typename T>
bool ckmax(T& a, const T& b) { return a < b ? a = b, true : false; }
// Output to 'cerr' if 'DEBUG' flag is set. Do nothing otherwise.
#ifndef DEBUG
#define DEBUG 0
#endif
#define dout if (DEBUG) cerr
// Output all passed variables with their corresponding name and value.
#define dvarimpl(...) mkDB(#__VA_ARGS__, __VA_ARGS__) << "\e[0m "
#define dvar(...) " \e[35m" << dvarimpl(__VA_ARGS__)
#define dvarr(...) " \e[31m" << dvarimpl(__VA_ARGS__)
#define dvarb(...) " \e[34m" << dvarimpl(__VA_ARGS__)
#define dvarg(...) " \e[32m" << dvarimpl(__VA_ARGS__)
#define dvary(...) " \e[33m" << dvarimpl(__VA_ARGS__)
#define dvarc(...) " \e[36m" << dvarimpl(__VA_ARGS__)
#define dvari(...) " \e[7m" << dvarimpl(__VA_ARGS__)

///////////////////////////////////////////////////////////////
// Utility functions.
///////////////////////////////////////////////////////////////

namespace impl {
  template <typename T, typename F, size_t... Is>
  F for_each(T& t, F f, index_sequence<Is...>) {
    auto l = { (f(get<Is>(t), Is), 0)... };
    (void) l;
    return f;
  }
}

template <typename... Ts, typename F>
F for_each(tuple<Ts...>& t, F f) {
  return impl::for_each(t, f, make_index_sequence<sizeof...(Ts)>{});
}

template <typename... Ts, typename F>
F for_each(const tuple<Ts...>& t, F f) {
  return impl::for_each(t, f, make_index_sequence<sizeof...(Ts)>{});
}


// IsC indicates whether a type defines a 'const_iterator'.
// IsC::value is true if 'const_iterator' exists and false otherwise.
template <typename T> true_type const_iterator_check(typename T::const_iterator*);
template <typename T> false_type const_iterator_check(...);
template <typename T> struct IsC : decltype(const_iterator_check<T>(nullptr)) {};
// No new input/output for string as those already exist.
template <> struct IsC<string> : false_type {};

///////////////////////////////////////////////////////////////
// Begin Output
///////////////////////////////////////////////////////////////

// Forward declarations.
template <typename T>
enable_if_t<IsC<T>::value, ostream&> operator<<(ostream&, const T&);
template <typename T1, typename T2>
ostream& operator<<(ostream&, const pair<T1, T2>&);

// Print each tuple element.
template <typename... Ts>
ostream& operator<<(ostream& o, const tuple<Ts...>& t) {
    o << '(';
    for_each(t, [&](auto& x, size_t i) { if(i) o << ", "; o << x; });
    return o << ')';
}

// Special case for 1-tuple to avoid confusing parentheses
template <typename T>
ostream& operator<<(ostream& o, const tuple<T>& t) {
  return o << get<0>(t);
}

// Output for pairs via above defined tuple output routine.
template <typename T1, typename T2>
ostream& operator<<(ostream& o, const pair<T1, T2>& p) {
  return o << '(' << p.fi << ", " << p.se << ')';
}

// Output every element in a container with 'begin' and 'end' iterators.
template <typename T>
enable_if_t<IsC<T>::value, ostream&> operator<<(ostream& o, const T& c) {
  o << '[';
  for (auto it = c.cbegin(); it != c.cend(); ++it)
    o << *it << (next(it) != c.cend() ? ", " : "");
  return o << ']';
}

///////////////////////////////////////////////////////////////
// Debug output
///////////////////////////////////////////////////////////////

template <typename... Ts>
struct DB {
  string n;
  tuple<Ts...> d;
  DB(const string& ns, Ts... ds) : n{ns}, d{ds...} {}
  friend ostream& operator<<(ostream& o, const DB& db) {
    int i = 0;
    for_each(db.d, [&](const auto& e, int idx) {
      (idx ? o << " " : o) << "[";
      while (i < SZ(db.n) and isspace(db.n[i])) ++i;
      int br = 0, str = 0, chr = 0, esc = 0;
      while (i < SZ(db.n)) {
        if (db.n[i] == '\\') esc = not esc;
        if (not chr and not esc and db.n[i] == '\"') str = not str;
        if (not str and not esc and db.n[i] == '\'') chr = not chr;
        if (not str and not chr) {
          br += brt(db.n[i]);
          if (db.n[i] == ',' and br == 0) {
            ++i;
            break;
          }
        }
        if (db.n[i] != '\\') esc = false;
        o << db.n[i++];
      }
      o << ": " << e << "]";
    });
    return o;
  }
  static inline int brt(char c) {
    switch (c) {
    case '(': case '[': case '{': return 1;
    case ')': case ']': case '}': return -1;
    default: return 0;
    }
  }
};
template <typename... Ts>
DB<Ts...> mkDB(const string& n, Ts... d) { return DB<Ts...>(n, d...); }

///////////////////////////////////////////////////////////////
// Pretty output
///////////////////////////////////////////////////////////////

// PrettyPrint struct that contains a value to be printed and
// a list of seperators which indicate how different dimensions
// of multidimensional values should be seperated.
template <typename T, size_t N>
struct PP {
  // Value to print.
  const T& v;
  // Pointer to seperator list.
  shared_ptr<array<string, N>> se;
  // Index of next seperator.
  size_t idx;
  PP(const T& value, shared_ptr<array<string, N>> p, size_t i = 0)
      : v{value}, se{p}, idx{i} {}
};

// If a value is not a pair, tuple or std-library-continer just print it.
// Pairs and tuples are implemented via template specialization further down.
template <typename T, size_t M>
enable_if_t<not IsC<T>::value, ostream&>
operator<<(ostream& o, const PP<T, M>& p) {
  return o << p.v;
}

// Prints every tuple element.
template <size_t M, typename... Ts>
ostream& operator<<(ostream& o, const PP<tuple<Ts...>, M>& p) {
  const string& sep = p.idx < M ? (*p.se)[p.idx] : " ";
  for_each(p.v, [&](auto& x, size_t i) {
    if(i) o << sep;
    o << PP<decay_t<decltype(x)>, M>(x, p.se, p.idx + 1);
  });
  return o;
}

// Print pairs with the specified seperator for that level.
template <typename T1, typename T2, size_t M>
ostream& operator<<(ostream& o, const PP<pair<T1, T2>, M>& p) {
  const string& sep = p.idx < M ? (*p.se)[p.idx] : " ";
  return o << PP<T1, M>(p.v.fi, p.se, p.idx + 1) << sep
           << PP<T2, M>(p.v.se, p.se, p.idx + 1);
}

// Print std-library-container with the specified seperator.
template <typename T, size_t M>
enable_if_t<IsC<T>::value, ostream&>
operator<<(ostream& o, const PP<T, M>& p) {
  // Seperator for the current layer (or default)
  const string& sep = p.idx < M ? (*p.se)[p.idx] : " ";
  // Print every container element
  for (auto it = p.v.cbegin(); it != p.v.cend(); ++it)
    o << PP<typename T::value_type, M>(*it, p.se, p.idx + 1)
      << (next(it) != p.v.cend() ? sep : "");
  return o;
}

// This function is the main way for a user to interface with the PrettyPrinter.
template <typename T, typename... Ts, size_t N = sizeof...(Ts)>
PP<T, N> pp(const T& value, Ts... seps) {
  return PP<T, N>(value, make_shared<array<string, N>>(array<string, N>{seps...}));
}

///////////////////////////////////////////////////////////////
// Begin Input
///////////////////////////////////////////////////////////////

// Forward declarations.
template <typename T>
enable_if_t<IsC<T>::value, istream&> operator>>(istream&, T&);
template <typename T1, typename T2>
istream& operator>>(istream&, pair<T1, T2>&);

// Read a tuple.
template <typename... Ts>
istream& operator>>(istream& i, tuple<Ts...>& t) {
  for_each(t, [&](auto& x, int) { i >> x; });
  return i;
}

// Read the contents of a 'pair' object.
template <typename T1, typename T2>
istream& operator>>(istream& i, pair<T1, T2>& p) {
  return i >> p.fi >> p.se;
}

// Read containers with 'begin' and 'end' iterators.
template <typename T>
enable_if_t<IsC<T>::value, istream&> operator>>(istream& i, T& v) {
  for (auto& x : v) i >> x;
  return i;
}
template<typename T>
set<T>& operator+=(set<T>& s, const T& e) {
  return s.insert(e), s;
}
template<typename T>
set<T>& operator-=(set<T>& s, const T& e) {
  return s.erase(e), s;
}
template<typename T>
set<T>& operator&=(set<T>& a, const set<T>& b) {
  set<T> o;
  set_intersection(ALL(a), ALL(b), inserter(o, o.begin()));
  return a.swap(o), a;
}
template<typename T>
set<T>& operator^=(set<T>& a, const set<T>& b) {
  set<T> o;
  set_symmetric_difference(ALL(a), ALL(b), inserter(o, o.begin()));
  return a.swap(o), a;
}
template<typename T>
set<T>& operator/=(set<T>& a, const set<T>& b) {
  set<T> o;
  set_difference(ALL(a), ALL(b), inserter(o, o.begin()));
  return a.swap(o), a;
}
template<typename T>
set<T>& operator|=(set<T>& a, const set<T>& b) {
  return a.insert(ALL(b)), a;
}
template<typename T>
set<T> operator&(set<T> a, const set<T>& b) {
  return a &= b;
}
template<typename T>
set<T> operator^(set<T> a, const set<T>& b) {
  return a ^= b;
}
template<typename T>
set<T> operator/(set<T> a, const set<T>& b) {
  return a /= b;
}
template<typename T>
set<T> operator|(set<T> a, const set<T>& b) {
  return a |= b;
}
template<typename T>
bool operator<(const set<T>& s, const T& e) {
  return static_cast<bool>(s.count(e));
}

template<typename F>
vector<string> input(F f) {
  vector<string> ss;
  for (string s; getline(cin, s); ss.pb(s)) {
    stringstream inp(s);
    f(inp);
  }
  return ss;
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);

  vector<pair<string, ll>> cs;
  input([&](auto& ss) {
    string s; ll v; ss >> s >> v;
    cs.eb(s, v);
  });

  auto type = [&](const string& s) -> int {
    set<char> u(ALL(s));
    if (SZ(u) == 5) {
      return 1;
    } else if (SZ(u) == 4) {
      return 2;
    } else if (SZ(u) == 3) {
      for (char c : s) {
        if (count(ALL(s), c) == 2) return 3;
        if (count(ALL(s), c) == 3) return 4;
      }
    } else if (SZ(u) == 2) {
      for (char c : s) {
        if (count(ALL(s), c) == 2) return 5;
        if (count(ALL(s), c) == 4) return 6;
      }
    } else {
      return 7;
    }
    return 0;
  };

  map<char, int> val;
  FOR (i, 2, 10) val['0' + i] = i;
  val['T'] = 10;
  val['J'] = 11;
  val['Q'] = 12;
  val['K'] = 13;
  val['A'] = 14;

  auto cmp = [&](const string& a, const string& b, auto t) -> bool {
    int ta = t(a), tb = t(b);
    if (ta < tb) return true;
    if (ta == tb) {
      F0R (i, 5) {
        if (val[a[i]] < val[b[i]]) return true;
        if (val[a[i]] > val[b[i]]) return false;
      }
    }
    return false;
  };

  sort(ALL(cs), [&](const auto& a, const auto& b) { return cmp(a.fi, b.fi, type); });

  ll sm = 0;
  F0R (i, SZ(cs)) sm += (i + 1) * cs[i].se;
  cout << sm << endl;

  auto type2 = [&](string s) -> int {
    int mx = 0;
    for (char c : "AKQT98765432") {
      string p = s;
      for (char& cc : p) if (cc == 'J') cc = c;
      ckmax(mx, type(p));
    }
    return mx;
  };

  val['J'] = 1;

  sort(ALL(cs), [&](const auto& a, const auto& b) { return cmp(a.fi, b.fi, type2); });

  sm = 0;
  F0R (i, SZ(cs)) sm += (i + 1) * cs[i].se;
  cout << sm << endl;

  return 0;
}