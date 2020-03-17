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

vi dp, parent, white;
vvi adj;
int dfs1(int v) {
    int val = white[v];
    for (int u : adj[v])
        if (u != parent[v]) {
            parent[u] = v;
            val += max(0, dfs1(u));
        }
    return dp[v] = val;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, t;
    cin >> n;
    white.assign(n, -1);
    F0R (i, n) {
        cin >> t;
        white[i] += 2 * t;
    }

    adj.assign(n, vi());
    dp.assign(n, -1);
    parent.assign(n, -1);
    F0R (i, n - 1) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        adj[a].pb(b);
        adj[b].pb(a);
    }

    dfs1(0);

    queue<int> q;
    for (int u : adj[0]) q.push(u);
    while (!q.empty()) {
        int i = q.ft;
        q.pop();
        if (dp[i] <= 0)
            dp[i] = max(dp[parent[i]] + dp[i], dp[i]);
        else
            dp[i] = max(dp[parent[i]], dp[i]);

        for (int u : adj[i])
            if (u != parent[i]) q.push(u);
    }

    F0R (i, n)
        cout << dp[i] << ' ';
    cout << endl;

    return 0;
}
