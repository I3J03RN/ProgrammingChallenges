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

int deg[1 << 20], ptr[1 << 20];
vi adj[1 << 20];
bitset<1 << 20> visited;
int mask;
vii ps;
int dfs(int v) {
    visited[v] = 1;
    int res = 1;
    for (int i : adj[v]) {
        int u = (v == (ps[i].fi & mask) ? ps[i].se : ps[i].fi) & mask;
        if (!visited[u]) {
            res += dfs(u);
        }
    }
    return res;
}

void solve() {
    int n;
    cin >> n;
    ps.resize(n);
    F0R (i, n) cin >> ps[i].fi >> ps[i].se;
    if (n == 1) {
        if (ps[0].fi == ps[0].se) {
            cout << 20 << endl;
        } else {
            cout << __builtin_ctz(ps[0].fi ^ ps[0].se) << endl; 
        }
        cout << 1 << ' ' <<  2 << endl;
        return;
    }
    int l = 0, r = 20;
    int first;
    while (l < r) {
        int mid = (l + r + 1) / 2, cnt = 0;
        bool ok = 1;
        mask = (1 << mid) - 1;
        first = -1;
        memset(deg, 0, sizeof(int) * (1 << mid));
        visited.reset();
        F0R (i, 1 << mid) {
            adj[i].clear();
        }
        F0R (i, n) {
            int u = ps[i].fi & mask, v = ps[i].se & mask;
            ++deg[u]; ++deg[v];
            adj[u].pb(i);
            if (u != v) {
                adj[v].pb(i);
            }
        }
        F0R (i, 1 << mid) {
            if (deg[i] & 1) {
                ok = 0;
                break;
            }
            if (deg[i]) {
                ++cnt;
                if (first == -1) first = i;
            }
        }

        ok = ok && cnt == dfs(first);
        if (ok) {
            l = mid;
        } else {
            r = mid - 1;
        }
    }
    cout << l << endl;
    mask = (1 << l) - 1;
    memset(ptr, 0, sizeof(int) * (1 << l));
    F0R (i, 1 << l) {
        adj[i].clear();
    }
    F0R (i, n) {
        int u = ps[i].fi & mask, v = ps[i].se & mask;
        adj[u].pb(i);
        if (u != v) {
            adj[v].pb(i);
        }
    }
    vector<bool> visited(n);
    deque<int> q;
    int cur = ps[0].fi & mask;
    while (n) {
        while (1) {
            while (ptr[cur] == SZ(adj[cur])) {
                F0R (_, 2) {
                    q.pb(q.front());
                    q.pop_front();       
                }
                if (q.back() & 1) {
                    cur = ps[q.back() / 2].fi;
                } else {
                    cur = ps[q.back() / 2 - 1].se;       
                }
                cur &= mask;
            }
            while (ptr[cur] < SZ(adj[cur]) && visited[adj[cur][ptr[cur]]]) {
                ++ptr[cur];
            }
            if (ptr[cur] < SZ(adj[cur])) break;
        }
        int idx = adj[cur][ptr[cur]++];
        visited[idx] = 1;
        ii b = mp(idx * 2 + 1, idx * 2 + 2);
        ii e = ps[idx];
        if ((e.fi & mask) != cur) {
            swap(b.fi, b.se);
            swap(e.fi, e.se);
        }
        q.pb(b.fi); q.pb(b.se);
        cur = e.se & mask;
        n--;
    }
    for (int i : q) {
        cout << i << ' ';
    }
    cout << endl;

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
