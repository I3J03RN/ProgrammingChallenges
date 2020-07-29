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

vi dfsNum, low;
int dfsCounter = 0;
int artiDfs(int v, vvi& adj, vi& a, int p = -1) {
    dfsNum[v] = low[v] = dfsCounter++;
    int children = 0;
    bool aP = false;
    for (int u : adj[v]) {
        if (u == p) continue;
        if (dfsNum[u] == -1) {
            ckmin(low[v], artiDfs(u, adj, a, v));
            if (low[u] >= dfsNum[v] && p != -1 && !aP) {
                a.pb(v);
                aP = true;
            }
            children++;
        } else
            ckmin(low[v], dfsNum[u]);
    }
    if (p == -1 && children > 1) a.pb(v);
    return low[v];
}
void findArtiPoints(vvi& adj, vi& artiP) {
    dfsNum.assign(SZ(adj), -1);
    low.assign(SZ(adj), -1);
    F0R (v, SZ(adj))
        if (dfsNum[v] == -1) artiDfs(v, adj, artiP);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    int tc = 1;
    while (cin >> n, n) {
        unordered_map<string, int> indece;
        array<string, 110> places;
        F0R (i, n) {
            cin >> places[i];
            indece.insert(mp(places[i], i));
        }
        int e;
        cin >> e;
        vvi adj(n);
        while (e--) {
            string a, b;
            cin >> a >> b;
            int ai = indece[a], bi = indece[b];
            adj[ai].pb(bi);
            adj[bi].pb(ai);
        }
        vi aP;
        findArtiPoints(adj, aP);
        if (tc != 1) cout << endl;
        cout << "City map #" << tc++ << ": " << SZ(aP) << " camera(s) found\n";
        sort(ALL(aP),
             [&](int a, int b) -> bool { return places[a] < places[b]; });
        for (int i : aP) cout << places[i] << endl;
    }

    return 0;
}
