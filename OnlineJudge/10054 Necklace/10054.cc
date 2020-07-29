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

vvi adj(51, vi(51));
bitset<51> visited;

int cnt_dfs(int v) {
    visited[v] = 1;
    int cnt = 1;
    FOR (u, 1, 51) {
	if (adj[min(u, v)][max(u, v)] && !visited[u]) {
	    cnt += cnt_dfs(u);
	}
    }
    return cnt;
}


void solve() {
    for (auto& v : adj) v.assign(51, 0);
    vi nxt(51, 1), deg(51, 0);
    int n;
    cin >> n;
    while (n--) {
	int a, b;
	cin >> a >> b;
        ++adj[min(a, b)][max(a, b)];
        ++deg[a];
	++deg[b];
    }
    bool ok = 1;
    for (int i : deg) {
	if (i && (i & 1)) {
	    ok = 0;
	    break;
	}
    }
    visited.reset();
    FOR (v, 1, 51) {
	if (deg[v]) {
	    ok &= 51 - count(ALL(deg), 0) == cnt_dfs(v);
	    break;
	}

    }
    if (!ok) {
	cout << "some beads may be lost" << endl;
	return;
    }
    
    queue<int> q;
    bitset<51> found;
    FOR (v, 1, 51) {
	if (deg[v]) {
	    found[v] = 1;
            q.push(v);
	    break;
	}
    }

    list<int> tour;
    tour.pb(q.front());
    unordered_map<int, list<int>::iterator> inTour;
    inTour[q.front()] = tour.begin();

    while (SZ(q)) {
        int v = q.front(); q.pop();
	list<int>::iterator ins = inTour[v];
	while (deg[v]) {
	    int seen = 0;
	    int c = v;
	    while (1) {
                if (c == v && 2 == ++seen) break; 
		tour.insert(ins, c);
		if (!found[c]) {
		    found[c] = 1;
		    q.push(c);
		    inTour[c] = prev(ins);
		}
		while (!adj[min(c, nxt[c])][max(c, nxt[c])]) ++nxt[c];
		--adj[min(c, nxt[c])][max(c, nxt[c])]; --deg[c]; --deg[nxt[c]];
		c = nxt[c];
	    }
        }
    }
    while (SZ(tour) > 1) {
	int a = tour.front();
	tour.pop_front();
	int b = tour.front();
	cout << a << ' ' << b << endl;
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int tt;
    cin >> tt;
    FOR (t, 1, tt + 1) {
	cout << "Case #" << t << endl;
	solve();
	if (t != tt) cout << endl;
    }

    return 0;
}
