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

vi as;

const int inf = 1e8;

struct ST {
    int n;
    vi sum, bestL, bestR;
    int inline left(int p) { return p << 1; }
    int inline right(int p) { return (p << 1) + 1; }
    tuple<int, int, int> build(int p, int L, int R) {
        if (L == R) {
            return mt(sum[p] = as[L], bestL[p] = max(0, as[L]), bestR[p] = max(0, as[L]));
        } else {
            auto [sl, bll, blr] = build(left(p), L, (R + L) / 2);
            auto [sr, brl, brr] = build(right(p), (R + L) / 2 + 1, R);
            sum[p] = sl + sr;
            bestL[p] = max(bll, sl + brl);
            bestR[p] = max(brr, sr + blr);
            return mt(sum[p], bestL[p], bestR[p]);
        }
    }
    tuple<int, int, int> query(int p, int L, int R, int i, int j) {
        if (i > R || j < L) return mt(0, -inf, -inf);
        if (i <= L && R <= j) return mt(sum[p], bestL[p], bestR[p]);
        auto [sl, bll, blr] = query(left(p), L, (R + L) / 2, i, j);
        auto [sr, brl, brr] = query(right(p), (R + L) / 2 + 1, R, i, j);
	return mt(sl + sr, max(bll, sl + brl), max(brr, sr + blr));

    }
    ST() : n(SZ(as)), sum(SZ(as) * 4), bestL(SZ(as) * 4), bestR(SZ(as) * 4) {
        build(1, 0, n - 1);
    }
    tuple<int, int, int> query(int i, int j) {
	if (i > j) return mt(0, 0, 0);
	return query(1, 0, n - 1, i, j); }
    void print(int p = 1, int L = 0, int R = SZ(as) - 1) {
	dout << dvar(p) << dvar(L) << dvar(R) << dvar(sum[p]) << dvar(bestL[p]) << dvar(bestR[p]) << endl;
	if (L == R) return;
	print(left(p), L, (L + R) / 2);
	print(right(p), (L + R) / 2 + 1, R);
    } 
};
vi _pos[100];
vi* pos = _pos + 50;
int _cur[100];
int* cur = _cur + 50;

void solve() {
    int n;
    cin >> n;
    as.resize(n);
    F0R (i, n)
        cin >> as[i];
    ST st;
    // st.print();
    // F0R (i, n) {
    // 	FOR (j, i, n) {
    // 	    auto [sum, bl, br] = st.query(i, j);
    // 	    dout << dvar(i) << dvar(j) << dvar(sum) << dvar(bl) << dvar(br) << endl;
    // 	}
    // }
    FOR (i, -30, 31) pos[i].pb(-1);
    F0R (i, n)
	pos[as[i]].pb(i);
    FOR (i, -30, 31) pos[i].pb(n);
    int best = 0;
    F0R (i, n) {
	++cur[as[i]];
	int l = -1, r = n;
	for (int a = as[i] + 1; a <= 30; ++a) {
	    ckmax(l, pos[a][cur[a]]);
	    ckmin(r, pos[a][cur[a] + 1]);
	}
	dout << dvar(l) << dvar(r) << endl;
	ckmax(best, get<2>(st.query(l + 1, i - 1)) + get<1>(st.query(i + 1, r - 1)));
    }
    cout << best << endl;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int tt = 1;
    FOR (t, 1, tt + 1) {
        // cout << "Case #" << t << ": ";
        solve();
    }

    return 0;
}
