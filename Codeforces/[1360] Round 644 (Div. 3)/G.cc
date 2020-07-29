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

const ll inf = 10e12;
struct edge {
    edge(int from, int to, ll capacity, ll flow = 0)
        : mfrom(from), mto(to), mcapacity(capacity), mflow(flow) {}
    int mfrom, mto;
    ll mcapacity, mflow;
    int other(int v) { return v == mfrom ? mto : mfrom; }
    ll capacity(int v = 0) { return v == mfrom ? mcapacity : 0; }
    ll flow(int v) { return v == mfrom ? mflow : -mflow; }
    void adjust(int v, ll amount) { mflow += v == mfrom ? amount : -amount; }
};
ostream& operator<<(ostream& o, edge e) {
    return o << e.mfrom << ' ' << e.mto << ' ' << e.mcapacity << ' ' << e.mflow;
}
vector<edge> edges;
vvi adj;
vi label;
vi currentEdge;
vector<ll> excess;
queue<int> active;
void push(int v, edge& e) {
    ll more = min(excess[v], e.capacity(v) - e.flow(v));
    excess[e.other(v)] += more;
    excess[v] -= more;
    e.adjust(v, more);
    if (more && excess[e.other(v)] == more) active.push(e.other(v));
}
void relabel(int v) {
    int m = numeric_limits<int>::max();
    for (int i : adj[v]) {
        auto& e = edges[i];
        if (e.flow(v) < e.capacity(v)) ckmin(m, label[edges[i].other(v)]);
    }
    if (m < numeric_limits<int>::max()) label[v] = m + 1;
}
void discharge(int v) {
    while (excess[v]) {
        auto& e = edges[adj[v][currentEdge[v]]];
        if (label[v] - 1 == label[e.other(v)] && e.flow(v) < e.capacity(v))
            push(v, e);
        else if (SZ(adj[v]) == ++currentEdge[v]) {
            currentEdge[v] = 0;
            relabel(v);
        }
    }
}
ll maxflow(int s, int t) {
    currentEdge.assign(SZ(adj), 0);
    label.assign(SZ(adj), 0);
    excess.assign(SZ(adj), 0);
    excess[s] = inf;
    label[s] = SZ(adj);
    for (int i : adj[s]) push(s, edges[i]);
    while (!active.empty()) {
        if (active.ft != s && active.ft != t) discharge(active.ft);
        active.pop();
    }
    ll maxflow = 0;
    for (int i : adj[s]) maxflow += edges[i].flow(s);
    return maxflow;
}

void addEdge(int from, int to, ll c, ll f = 0) {
    edges.eb(from, to, c, f);
    adj[from].pb(SZ(edges) - 1);
    adj[to].pb(SZ(edges) - 1);
}

void solve() {
    int n, m, a, b;
    cin >> n >> m >> a >> b;
    if (n * a != m * b) {
        cout << "NO" << endl;
        return;
    }
    adj.assign(n + m + 2, vi());
    F0R (i, n)
        F0R (j, m)
            addEdge(i, n + j, 1);

    int s = n + m;
    int t = s + 1;
    F0R (i, n) { addEdge(s, i, a); }
    F0R (i, m) { addEdge(n + i, t, b); }
    if (maxflow(s, t) == n * a) {
        cout << "YES" << endl;
        F0R (i, n) {
            F0R (j, m) { cout << edges[i * m + j].flow(i); }
            cout << endl;
        }
    } else
        cout << "NO" << endl;
    edges.clear();
    adj.clear();
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int tt;
    cin >> tt;
    while (tt--) solve();

    return 0;
}
