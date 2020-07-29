#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
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
#define SZ(x) (x).size()
#define ft front()
#define bk back()
#define ins insert
#define ge(a, b) get<(b)>((a))
#define MID(a, b) (a + b) / 2
#define FOR(a, b, c) for (auto(a) = (b); (a) < (c); ++(a))
#define ROF(a, b, c) for (auto(a) = (b); (a) > (c); --(a))
#define F0R(a, b) for (auto(a) = 0; (a) < (b); ++(a))
#define R0F(a, b) for (auto(a) = (b); (a) >= 0; --(a))
#define FORI(a, b) for (auto(a) = (b).begin(); (a) != (b).end(); ++(a))
#define ROFI(a, b) for (auto(a) = (b).rbegin(); (a) != (b).rend(); ++(a))
#define TRAV(a, b) for (auto&(a) : (b))
const int xd[4] = {0, 1, 0, -1}, yd[4] = {1, 0, -1, 0};
template <typename t>
bool ckmin(t& a, const t& b) {
    return a > b ? a = b, true : false;
}
template <typename t>
bool ckmax(t& a, const t& b) {
    return a < b ? a = b, true : false;
}

const int inf = 1e9;

bool bellmanFordQueue(vvii& adj, vi& dist, int start) {
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
        for (ii i : adj[v]) {
            if (ckmin(dist[i.fi], dist[v] + i.se)) {
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

    int n;
    cin >> n;

    vvii adj(n);

    FOR (r, 1, n)
        F0R (c, r) {
            while (cin.peek() != 'x' && !isdigit(cin.peek())) cin.get();
            if (cin.peek() == 'x') {
                cin.get();
                continue;
            }
            int d;
            cin >> d;
            adj[r].eb(c, d);
            adj[c].eb(r, d);
        }
    if (n == 1)
        cout << 0 << endl;
    else {
        vi dist;
        bellmanFordQueue(adj, dist, 0);
        cout << *max_element(dist.begin() + 1, dist.end()) << endl;
    }

    return 0;
}
