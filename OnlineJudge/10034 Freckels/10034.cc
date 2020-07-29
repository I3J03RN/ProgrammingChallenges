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
#define pf push_front
#define eb emplace_back
#define pb push_back
#define mp make_pair
#define mt make_tuple
#define SZ(x) (int)(x).size()
#define ft front()
#define bk back()
// #define endl '\n'
#define FOR(a, b, c) for (auto(a) = (b); (a) < (c); ++(a))
#define ROF(a, b, c) for (auto(a) = (b); (a) > (c); --(a))
#define F0R(a, b) FOR ((a), 0, (b))
#define R0F(a, b) ROF ((a), (b), -1)
#define CEIL(a, b) ((a) + (b)-1) / (b)
#define SET(a, b) memset((a), (b), sizeof(a))
template <class t>
bool ckmin(t& a, const t& b) {
    return a > b ? a = b, true : false;
}
template <class t>
bool ckmax(t& a, const t& b) {
    return a < b ? a = b, true : false;
}
#ifndef DEBUG
#define DEBUG 0
#endif
#define dout \
    if (DEBUG) std::cerr
#define dvar(...) " [" << #__VA_ARGS__ ": " << (__VA_ARGS__) << "] "
template <class a, class b>
ostream& operator<<(ostream& o, const pair<a, b>& p);
template <class T>
struct IsC {
    template <class C>
    static char test(typename C::const_iterator*);
    template <class C>
    static int test(...);
    static const bool value = sizeof(test<T>(0)) == sizeof(char);
};
template <>
struct IsC<string> {
    static const bool value = false;
};
template <class C>
typename enable_if<IsC<C>::value, ostream&>::type operator<<(ostream& o,
                                                             const C& c) {
    o << '[';
    for (auto it = c.begin(); it != c.end();)
        o << *it << (++it != c.end() ? ", " : "");
    return o << ']';
}
template <class a, class b>
ostream& operator<<(ostream& o, const pair<a, b>& p) {
    return o << '(' << p.fi << ", " << p.se << ')';
}


class unionFind {
 public:
  unionFind(int size) : msize(size), data(size, -1) {}
  bool sameSet(int a, int b) { return find(a) == find(b); }
  int find(int x) {
      dout << dvar(x) << endl;
    return data[x] < 0 ? x : data[x] = find(data[x]);
  }
  bool join(int a, int b) {
    a = find(a), b = find(b);
    if (a == b) return false;
    if (data[a] > data[b]) swap(a, b);
    data[a] += data[b], data[b] = a;
    return --msize, true;
  }
  int size() { return msize; }
  int size(int a) { return -data[find(a)]; }

 private:
  int msize;
  vi data;
};

typedef tuple<int, int, double> iid;
double kruskal(vector<iid>& edges, int V, vi& mst) {
  sort(ALL(edges),
       [](iid& a, iid& b) -> bool { return get<2>(a) < get<2>(b); });
  unionFind uf(V);
  double weigth = 0;
  for (int i = 0; SZ(uf) > 1; ++i) {

    if (uf.join(get<0>(edges[i]), get<1>(edges[i]))) {
      mst.pb(i);
      weigth += get<2>(edges[i]);
    }
  }
  return weigth;
}

void solve() {
    static bool first = 1;
    if (first) first = 0;
    else cout << endl;

    int n;
    cin >> n;
    vector<pair<double, double>> fs(n);
    F0R (i, n) cin >> fs[i].fi >> fs[i].se;

    vector<iid> edges;
    F0R (i, n) {
	FOR (j, i + 1, n) {
	    edges.eb(i, j, hypot(fs[i].fi - fs[j].fi, fs[i].se - fs[j].se));
	}
    }
    for (auto [a, b, d] : edges) dout << dvar(a) << dvar(b) << dvar(d) << endl;
    vi mst;
    cout << setprecision(2) << fixed << kruskal(edges, n, mst) << endl;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int tt;
    cin >> tt;
    FOR (t, 1, tt + 1) {
	// cout << "Case #" << t << ": ";
	solve();
    }

    
    return 0;
}
