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

const ll p = 1000000007;

vvi adj;
vector<ll> fac;
vector<ll> dp;
vector<ll> cnt;

ll binpow(ll a, ll b) {
    a %= p;
    ll res = 1;
    while (b > 0) {
        if (b & 1) res = res * a % p;
        a = a * a % p;
        b >>= 1;
    }
    return res;
}

void dfs(int v = 0, int parent = -1) {
    for (int u : adj[v]) {
        if (u != parent) {
            dfs(u, v);
            dp[v] = dp[v] * dp[u] % p;
            dp[v] = dp[v] * binpow(fac[cnt[u]], p - 2) % p;
            cnt[v] += cnt[u];
        }
    }
    dp[v] = dp[v] * fac[cnt[v] - 1] % p;
}

void dfs2(int v = 0, int parent = -1) {
    if (parent != -1) {
        ll tmp = dp[parent] * binpow(fac[cnt[parent] - 1], p - 2) % p;
        tmp = tmp * fac[cnt[v]] % p;
        tmp = tmp * binpow(dp[v], p - 2) % p;
        tmp = tmp * fac[cnt[parent] - cnt[v] - 1] % p;

        dp[v] = dp[v] * binpow(fac[cnt[v] - 1], p - 2) % p;
        dp[v] = dp[v] * binpow(fac[cnt[parent] - cnt[v]], p - 2) % p;
        dp[v] = dp[v] * tmp % p;
        cnt[v] = cnt[parent];
        dp[v] = dp[v] * fac[cnt[v] - 1] % p;
    }
    for (int u : adj[v])
        if (u != parent) dfs2(u, v);
}
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;
    adj.assign(n, vi());
    F0R (i, n - 1) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        adj[a].pb(b);
        adj[b].pb(a);
    }
    fac.assign(n + 1, 1);
    FOR (i, 1, n + 1)
        fac[i] = i * fac[i - 1] % p;
    cnt.assign(n, 1);
    dp.assign(n, 1);
    dfs();
    // for (ll l : dp) cout << l << endl;
    dfs2();

    for (ll l : dp) cout << l << endl;

    return 0;
}
