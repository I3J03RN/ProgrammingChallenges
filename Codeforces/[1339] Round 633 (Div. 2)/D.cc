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

int main() {
    ios_base::sync_with_stdio(0);
    cout.tie(0);

    int n;
    cin >> n;
    adj.assign(n, vi());
    F0R (i, n - 1) {
        int a, b;
        cin >> a >> b;
        --a;
        --b;
        adj[a].pb(b);
        adj[b].pb(a);
    }

    vi visited(n, -1);
    queue<ii> q;
    bool allEven = true;
    F0R (i, n) {
        if (SZ(adj[i]) == 1) {
            visited[i] = 0;
            q.emplace(i, 0);
        }
    }
    while (!q.empty()) {
        auto [v, d] = q.ft;
        q.pop();
        for (int u : adj[v]) {
            if (visited[u] == -1) {
                visited[u] = d + 1;
                q.emplace(u, d + 1);
            } else {
                if ((visited[u] + d + 1) & 1) allEven = false;
            }
        }
    }

    set<int> parents;
    int non = 0;
    F0R (i, n) {
        if (SZ(adj[i]) == 1) {
            if (parents.count(adj[i][0]) == 1)
                ++non;
            else
                parents.insert(adj[i][0]);
        }
    }
    cout << (allEven ? 1 : 3) << ' ' << n - 1 - non << endl;
    return 0;
}
