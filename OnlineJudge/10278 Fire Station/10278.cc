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

int f, n;
vector<bool> isStation;
vvii adj;
vvi dist;

const int inf = 1e9;
void djikstra(vi& dist, int start) {
    dist.assign(SZ(adj), inf);
    auto cmp = [](ii& a, ii& b) -> bool { return a.se > b.se; };
    priority_queue<ii, vii, decltype(cmp)> q(cmp);
    q.push(mp(start, 0));
    dist[start] = 0;
    while (!q.empty()) {
        int v = q.top().fi;
        int d = q.top().se;
        q.pop();
        if (dist[v] < d) continue;
        for (ii p : adj[v])
            if (ckmin(dist[p.fi], d + p.se)) q.push(mp(p.fi, d + p.se));
    }
}

void solve() {
    static bool first = true;
    if (first)
        first = false;
    else
        cout << endl;
    cin >> f >> n;
    isStation.assign(n, false);
    F0R (_, f) {
        int t;
        cin >> t;
        isStation[t - 1] = true;
    }
    adj.assign(n, vii());
    dist.assign(n, vi());

    cin.get();
    while (1) {
        string s;
        getline(cin, s);
        dout << dvar(s) << endl;
        if (s.empty()) break;
        stringstream ss(s);
        int a, b, d;
        ss >> a >> b >> d;
        dout << dvar(a) << dvar(b) << dvar(d) << endl;
        --a;
        --b;
        adj[a].eb(b, d);
        adj[b].eb(a, d);
    }

    F0R (i, n)
        djikstra(dist[i], i);

    vi nearest(n, inf);
    F0R (i, n) {
        F0R (j, n) {
            if (isStation[j]) ckmin(nearest[i], dist[i][j]);
        }
    }
    dout << dvar(nearest) << endl;
    int best = *max_element(ALL(nearest));
    int besti = 0;
    F0R (i, n) {
        int better = 0;
        if (isStation[i]) continue;
        F0R (j, n) { ckmax(better, min(dist[i][j], nearest[j])); }
        if (ckmin(best, better)) besti = i;
    }

    cout << besti + 1 << endl;

    adj.clear();
    dist.clear();
    isStation.clear();
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int tt;
    cin >> tt;
    while (tt--) solve();

    return 0;
}
