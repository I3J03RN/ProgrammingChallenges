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

void insert(vvi& adj, vi& num, const string& s) {
    int node = 0;
    for (char c : s) {
        if (adj[node][c - 'A'] == -1) {
            adj.eb(26, -1);
            num.eb(0);
            adj[node][c - 'A'] = SZ(adj) - 1;
        }
        node = adj[node][c - 'A'];
        ++num[node];
    }
}

ii dfs(vvi& adj, vi& num, int v, int depth, int k) {
    int used = 0, score = 0;
    for (int u : adj[v])
        if (u != -1) {
            ii p = dfs(adj, num, u, depth + 1, k);
            used += p.fi;
            score += p.se;
        }
    return mp(num[v] - (num[v] % k), score + depth * ((num[v] - used) / k));
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int tcs;
    cin >> tcs;
    FOR (tc, 1, tcs + 1) {
        int n, k;
        cin >> n >> k;
        vvi adj;
        vi num(1, 0);
        adj.eb(26, -1);
        F0R (i, n) {
            string s;
            cin >> s;
            insert(adj, num, s);
        }
        cout << "Case #" << tc << ": " << dfs(adj, num, 0, 0, k).se << endl;
    }

    return 0;
}
