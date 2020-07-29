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

class unionFind {
   public:
    unionFind(int size) : _size(size), data(size, -1) {}
    int find(int toFind) {
        int root = toFind;
        while (data[root] >= 0) root = data[root];
        while (toFind != root) {
            int tmp = data[toFind];
            data[toFind] = root;
            toFind = tmp;
        }
        return root;
    }
    void join(int a, int b) {
        a = find(a);
        b = find(b);
        if (data[a] < data[b]) {
            data[a] += data[b];
            data[b] = a;
        } else {
            data[b] += data[a];
            data[a] = b;
        }
        _size--;
    }
    int size() { return _size; }

   private:
    vi data;
    int _size;
};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, k, r;
    cin >> n >> k >> r;

    vvi adj(n);
    FOR (i, 1, n) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        adj[a].pb(b);
        adj[b].pb(a);
    }
    vi restStops;
    restStops.reserve(r);
    while (r--) {
        int i;
        cin >> i;
        restStops.pb(i - 1);
    }
    unionFind uf(n);
    vector<bool> visited(n, false);
    queue<ii> q;
    for (int rs : restStops) {
        visited[rs] = true;
        q.push(mp(rs, k));
    }
    while (!q.empty()) {
        auto [v, d] = q.ft;
        q.pop();
        if (d > 0) {
            for (int u : adj[v]) {
                uf.join(u, v);
                if (!visited[u]) {
                }
            }
        }
    }

    return 0;
}
