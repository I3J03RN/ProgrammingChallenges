#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
typedef vector<vi> vvi;
typedef vector<vii> vvii;
typedef complex<int> ci;
typedef complex<double> cd;
#define fi first
#define se second
#define ALL(x) (x).begin(), (x).end()
#define RALL(x) (x).rbegin(), (x).rend()
#define pf push_front
#define eb emplace_back
#define pb push_back
#define mp make_pair
#define mt make_tuple
#define ge(a, b) get<(b)>((a))
#define SZ(x) (x).size()
#define ft front()
#define bk back()
#define ins insert
#define endl '\n'
#define FOR(a, b, c) for (auto(a) = (b); (a) < (c); ++(a))
#define ROF(a, b, c) for (auto(a) = (b); (a) > (c); --(a))
#define F0R(a, b) FOR ((a), 0, (b))
#define R0F(a, b) ROF ((a), (b), -1)
#define FORI(a, b) for (auto(a) = (b).begin(); (a) != (b).end(); ++(a))
#define ROFI(a, b) for (auto(a) = (b).rbegin(); (a) != (b).rend(); ++(a))
#define CEIL(a, b) ((a) + (b)-1) / (b)
const int xd[4] = {0, 1, 0, -1}, yd[4] = {1, 0, -1, 0};
template <typename t>
bool ckmin(t& a, const t& b) {
    return a > b ? a = b, true : false;
}
template <typename t>
bool ckmax(t& a, const t& b) {
    return a < b ? a = b, true : false;
}

typedef pair<int, double> id;
typedef vector<vector<id>> vvid;
typedef vector<double> vd;

const double inf = 1e9;
bool bellmanFordQueue(vvid& adj, vd& dist, int start) {
    const int n = SZ(adj);
    dist.assign(n, inf);
    queue<int> q;
    vector<bool> inQ(n, false);
    // count number relaxations for every
    // vertex to account for negative circles
    vi cnt(n, 0);
    q.push(start);
    dist[start] = 0;
    inQ[start] = true;
    while (!q.empty()) {
        int v = q.ft;
        q.pop();
        inQ[v] = false;
        for (id i : adj[v]) {
            if (ckmin(dist[i.fi], max(i.se, dist[v]))) {
                if (++cnt[i.fi] > n) return false;
                if (!inQ[i.fi]) {
                    q.push(i.fi);
                    inQ[i.fi] = true;
                }
            }
        }
    }

    return true;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, tc = 1;
    while (cin >> n, n) {
        vii coords;
        coords.reserve(n);
        F0R (i, n) {
            int x, y;
            cin >> x >> y;
            coords.eb(x, y);
        }
        vvid adj(n);
        F0R (a, n)
            FOR (b, a + 1, n) {
                double dist = hypot((double)coords[a].fi - coords[b].fi,
                                    (double)coords[a].se - coords[b].se);
                adj[a].eb(b, dist);
                adj[b].eb(a, dist);
            }
        vd dist;
        bellmanFordQueue(adj, dist, 0);
        cout << "Scenario #" << tc++ << endl;
        cout << "Frog Distance = " << fixed << setprecision(3) << dist[1]
             << endl
             << endl;
    }

    return 0;
}
