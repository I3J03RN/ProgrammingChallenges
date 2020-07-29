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

struct node {
    // node, usesLeft, bootLeft, distance
    int v, ul, bl, d;
    node(int v, int ul, int bl, int d) : v{v}, ul{ul}, bl{bl}, d{d} {}
};

int a, b, l, k;
vvii adj;

const int inf = 1e9;
int djikstra() {
    vector<vvi> dist(a + b, vvi(k + 1, vi(l, inf)));
    auto cmp = [](node& a, node& b) -> bool { return a.d > b.d; };
    priority_queue<node, vector<node>, decltype(cmp)> q(cmp);
    q.emplace(0, k, 0, 0);
    dist[0][k][0] = 0;
    while (!q.empty()) {
	node n = q.top();
	if (n.v == a + b - 1) return n.d; 
	q.pop();
	if (dist[n.v][n.ul][n.bl] < n.d) continue;
	if (n.v >= a) n.bl = 0;
	for (ii p : adj[n.v]) {
	    int u = p.fi, ud = p.se;
	    // use new boot
	    if (n.ul && ud <= l && ckmin(dist[u][n.ul - 1][l - ud], n.d)) {
		q.emplace(u, n.ul - 1, l - ud, n.d);
	    }
	    if (n.bl >= ud && ckmin(dist[u][n.ul][n.bl - ud], n.d)) {
		q.emplace(u, n.ul, n.bl - ud, n.d);
	    }
	    if (ckmin(dist[u][n.ul][0], n.d + ud)) {
		q.emplace(u, n.ul, 0, n.d + ud);
	    }
	}
	     
    }
    assert(false);
    return 0;
}

void solve() {
    int m;
    cin >> a >> b >> m >> l >> k;
    adj.assign(a + b, vii());
    while (m--) {
	int x, y, d;
	cin >> x >> y >> d;
	--x; --y;
	adj[x].eb(y, d);
	adj[y].eb(x, d);
    }

    cout << djikstra() << endl;

    adj.clear();
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
