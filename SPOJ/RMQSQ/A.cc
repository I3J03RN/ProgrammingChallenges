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
#define endl '\n'
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

struct SPT {
  vvi spT, idx; // min value, pos of min value
  SPT(vi& A) {
  const int logn = ceil(log2l(SZ(A))) + 1;
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
    dout << dvar(l) << dvar(r) << dvar(k) << endl;
    return min(mp(spT[l][k], idx[l][k]),
               mp(spT[r - (1 << k) + 1][k], idx[l][k]));
  }
};

void solve() {
    int n, q;
    cin >> n;
    vi A(n);
    F0R (i, n) cin >> A[i];
    SPT spt(A);
    cin >> q;
    for (auto& v : spt.spT) dout << dvar(v) << endl;
    while (q--) {
	int l, r;
	cin >> l >> r;
	cout << spt.rmq(min(l, r), max(l, r)).fi << endl;
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int tt = 1;
    // cin >> tt;
    FOR (t, 1, tt + 1) {
	// cout << "Case #" << t << ": ";
	solve();
    }

    return 0;
}
