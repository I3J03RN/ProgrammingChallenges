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

vi dfsNum, low;
int dfsCounter = 0;
int bridgeDfs(int v, vvi& adj, vii& b, int p = -1) {
    dfsNum[v] = low[v] = dfsCounter++;
    for (int u : adj[v]) {
        if (u == p) continue;
        if (dfsNum[u] == -1) {
            ckmin(low[v], bridgeDfs(u, adj, b, v));
            if (low[u] > dfsNum[v]) b.eb(min(v, u), max(v, u));
        } else
            ckmin(low[v], dfsNum[u]);
    }
    return low[v];
}
void findBridges(vvi& adj, vii& bridges) {
    dfsNum.assign(SZ(adj), -1);
    low.assign(SZ(adj), -1);
    F0R (v, SZ(adj))
        if (dfsNum[v] == -1) bridgeDfs(v, adj, bridges);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    while (1) {
        int n;
        cin >> n;
        if (cin.eof()) break;
        vvi adj(n);
        F0R (i, n) {
            int v, e;
            cin >> v;
            while (!isdigit(cin.peek())) cin.get();
            cin >> e;
            while (!isdigit(cin.peek())) cin.get();
            while (e--) {
                int u;
                cin >> u;
                adj[v].pb(u);
            }
        }
        vii bridges;
        findBridges(adj, bridges);
        cout << SZ(bridges) << " critical links\n";
        sort(ALL(bridges));
        for (ii i : bridges) {
            cout << i.fi << " - " << i.se << endl;
        }
        cout << endl;
    }
    return 0;
}
