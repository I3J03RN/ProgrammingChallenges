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
// #define endl '\n'
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

vi height;
vi eularianTour;
vi first;
vvi adj;
const int MAXN = 1e6, K = 24;
int st[MAXN + 1][K + 1];

void sparsePre() {
    F0R (i, SZ(eularianTour))
        st[i][0] = height[eularianTour[i]];
    FOR (j, 1, K + 1) {
        for (int i = 0; i + (1 << j) <= SZ(eularianTour); ++i)
            st[i][j] = min(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
    }
}

int rmq(int a, int b) {
    int j = 31 - __builtin_clz(b - a + 1);
    return min(st[a][j], st[b - (1 << j) + 1][j]);
}

void dfs(int v, int h = 0) {
    eularianTour.pb(v);
    first[v] = SZ(eularianTour) - 1;
    height[v] = h;
    for (int u : adj[v]) {
        if (first[u] == -1) {
            dfs(u, h + 1);
            eularianTour.pb(v);
        }
    }
}
void lcaPre(int root = 0) {
    height.assign(SZ(adj), -1);
    first.assign(SZ(adj), -1);
    dfs(root);
    sparsePre();
}
int lca(int a, int b) {
    return rmq(min(first[a], first[b]), max(first[a], first[b]));
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;
    adj.assign(n, vi());
    FOR (i, 1, n) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        adj[a].pb(b);
        adj[b].pb(a);
    }
    lcaPre();
    int qs;
    cin >> qs;
    while (qs--) {
        int x, y, a, b, k;
        cin >> x >> y >> a >> b >> k;
        x--, y--, a--, b--;
        int v = lca(a, b);
        int p = height[a] - v + height[b] - v;
        if (p <= k && !((k - p) & 1)) {
            cout << "YES\n";
            continue;
        }
        int xa = lca(a, x), yb = lca(b, y);
        int pxa = height[a] - xa + height[x] - xa;
        int pyb = height[b] - yb + height[y] - yb;
        p = pxa + pyb + 1;
        if (p <= k && !((k - p) & 1)) {
            cout << "YES\n";
            continue;
        }
        int ya = lca(a, y), xb = lca(b, x);
        int pya = height[a] - ya + height[y] - ya;
        int pxb = height[b] - xb + height[x] - xb;
        p = pya + pxb + 1;
        if (p <= k && !((k - p) & 1)) {
            cout << "YES\n";
            continue;
        }
        cout << "NO\n";
    }

    return 0;
}
