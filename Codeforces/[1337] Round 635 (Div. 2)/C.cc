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
#define ge(a, b) get<(b)>((a))
#define SZ(x) (x).size()
#define ft front()
#define bk back()
#define endl '\n'
#define FOR(a, b, c) for (auto(a) = (b); (a) < (c); ++(a))
#define ROF(a, b, c) for (auto(a) = (b); (a) > (c); --(a))
#define F0R(a, b) FOR ((a), 0, (b))
#define R0F(a, b) ROF ((a), (b), -1)
#define CEIL(a, b) ((a) + (b)-1) / (b)
#define SET(a, b) memset((a), (b), sizeof(a))
#ifndef DEBUG
#define DEBUG 0
#endif
#define dout \
    if (DEBUG) std::cerr
const int xd[4] = {0, 1, 0, -1}, yd[4] = {1, 0, -1, 0};
template <typename t>
bool ckmin(t& a, const t& b) {
    return a > b ? a = b, true : false;
}
template <typename t>
bool ckmax(t& a, const t& b) {
    return a < b ? a = b, true : false;
}

vvi adj;
vi cnt, d;

void dfs(int v = 0, int p = -1) {
    if (~p) d[v] = 1 + d[p];
    for (int u : adj[v]) {
        if (u != p) {
            dfs(u, v);
            cnt[v] += 1 + cnt[u];
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cout.tie(0);

    int n, k;
    cin >> n >> k;
    cnt.assign(n, 0);
    d.assign(n, 0);
    adj.assign(n, vi());
    F0R (i, n - 1) {
        int a, b;
        cin >> a >> b;
        --a;
        --b;
        adj[a].pb(b);
        adj[b].pb(a);
    }
    dfs();
    vi sol(n - 1);
    iota(ALL(sol), 1);
    sort(RALL(sol),
         [&](int a, int b) { return d[a] - cnt[a] < d[b] - cnt[b]; });
    ll ans = 0;
    F0R (i, k)
        ans += d[sol[i]] - cnt[sol[i]];

    cout << ans << endl;

    return 0;
}
