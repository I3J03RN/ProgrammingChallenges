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
    o << '{';
    for (auto it = c.begin(); it != c.end();)
        o << *it << (++it != c.end() ? ", " : "}");
    return o;
}
template <class a, class b>
ostream& operator<<(ostream& o, const pair<a, b>& p) {
    return o << '(' << p.fi << ", " << p.se << ')';
}

const ll inf = 10e12;
struct edge {
    edge(int from, int to, ll maxf)
        : from(from), too(to), maxf(maxf), currentf(0) {}
    int from, too;
    ll maxf;
    ll currentf;
    int to(int v) { return v == from ? too : from; }
    ll mf(int v = 0) { return maxf; }
    ll curf(int v) { return v == from ? currentf : maxf - currentf; }
    ll flow(int v) { return mf(v) - curf(v); }
    void adjust(int v, ll amount) {
        if (v == from)
            currentf += amount;
        else
            currentf -= amount;
    }
};
ostream& operator<<(ostream& o, const edge& e) {
    return o << dvar(e.from) << dvar(e.too) << dvar(e.maxf) << dvar(e.currentf);
}
vector<edge> edges;
vvi adj;
ll augment(const ll s, const ll t) {
    vii p(SZ(adj), mp(-1, -1));
    queue<ll> q;
    p[s] = mp(-2, 0);
    q.push(s);
    while (!q.empty()) {
        ll v = q.front();
        if (v == t) break;
        q.pop();
        for (int i : adj[v])
            if (p[edges[i].to(v)] == mp(-1, -1) &&
                edges[i].curf(v) < edges[i].mf(v)) {
                p[edges[i].to(v)] = mp(v, i);
                q.push(edges[i].to(v));
            }
    }
    if (p[t] == mp(-1, -1)) return 0;
    ll mf = inf;
    for (ii c = p[t]; c.fi != -2; c = p[c.fi])
        ckmin(mf, edges[c.se].flow(c.fi));
    for (ii c = p[t]; c.fi != -2; c = p[c.fi]) edges[c.se].adjust(c.fi, mf);
    return mf;
}
void addEdge(int from, int to, ll cost) {
    edges.eb(from, to, cost);
    adj[from].pb(SZ(edges) - 1);
    adj[to].pb(SZ(edges) - 1);
}
ll maxflow(int s, int t) {
    ll maxflow = 0;
    while (ll plus = augment(s, t)) maxflow += plus;
    return maxflow;
}
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int m, w;
    while (cin >> m >> w, m) {
        edges.clear();
        vi in(m + 1), out(m + 1);
        FOR (i, 1, m + 1) {
            in[i] = i * 2 - 1;
            out[i] = i * 2;
        }

        adj.assign(m * 2 + 1, vi());

        addEdge(in[1], out[1], inf);
        addEdge(in[m], out[m], inf);
        F0R (i, m - 2) {
            int id;
            ll cost;
            cin >> id >> cost;
            addEdge(in[id], out[id], cost);
        }
        F0R (i, w) {
            int a, b;
            ll cost;
            cin >> a >> b >> cost;
            addEdge(out[a], in[b], cost);
            addEdge(out[b], in[a], cost);
        }
        cout << maxflow(in[1], out[m]) << endl;
        // for (auto& e : edges) cout << e << endl;
    }
}
