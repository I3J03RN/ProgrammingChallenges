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

vvii adj;

// vi dp;

// // used, num
// vii edges;

// int dfs1(int u = 0, int p = -1) {
//     for (auto [v, l] : adj[u])
//         if (v != p) dp[u] += dfs1(v, u);

//     return dp[u];
// }

// void dfs2(int u = 0, int p = -1) {
//     for (auto [v, num] : adj[u])
//         if (v != p) {
//             edges.eb(abs(dp[u] - dp[v] - dp[v]), num);
//             dfs2(v, u);
//         }
//}

vi in;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;
    adj.assign(n, vii());
    in.assign(n, 0);
    // dp.assign(n, 1);
    F0R (i, n - 1) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        in[a]++;
        in[b]++;
        adj[a].pb(mp(b, i));
        adj[b].pb(mp(a, i));
    }

    vi sol(n - 1, -1);
    vector<bool> seen(n, 0);
    queue<int> q;
    F0R (i, n) {
        if (in[i] == 1) {
            q.push(i);
            seen[i] = 1;
        }
    }
    int cnt = 0;
    while (!q.empty()) {
        int v = q.ft;
        q.pop();
        for (auto [u, num] : adj[v]) {
            if (sol[num] == -1) {
                sol[num] = cnt++;
            }
            if (!seen[u]) {
                q.push(u);
                seen[u] = 1;
            }
        }
    }

    for (int i : sol) cout << i << endl;

    return 0;
}
