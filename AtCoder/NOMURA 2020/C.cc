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

const ll maxLeafs = 1e8;

void solve() {
    int n;
    cin >> n;
    vector<ll> as(n + 1);
    F0R (i, n + 1) cin >> as[i];
    if (as[0] == 1) {
	if (n == 0) {
	    cout << 1 << endl;
	} else {
	    cout << -1 << endl;
	}
	return;
    }
    if (as[0] > 1) {
	cout << -1 << endl;
	return;
    }
    vector<ll> low(n + 1, 1), high(n + 1, 1);
    FOR (i, 1, n + 1) {
	if (high[i - 1] * 2 < as[i]) {
	    cout << -1 << endl;
	    return;
	}
	high[i] = min(high[i - 1] * 2 - as[i], (n - i) * maxLeafs);
	low[i] = max(low[i] - as[i], 0ll);
	dout <<  dvar(low[i]) << dvar(high[i]) << endl;
    }
    if (low[n] > 0) {
	cout << -1 << endl;
	return;
    }
    ll cnt = 1 + as[n], nodes = as[n];
    
    for (int i = n - 1; i; --i) {
	nodes = min(nodes + as[i], high[i] + as[i]);
	cnt += nodes;
    }
    cout << cnt << endl;
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
