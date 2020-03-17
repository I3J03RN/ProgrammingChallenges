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
//#define endl '\n'
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

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;
    vvi adj(n + 1);
    vi in(n + 1, 0);
    F0R (i, n - 1) {
        int a, b;
        cin >> a >> b;
        adj[a].pb(b);
        adj[b].pb(a);
        in[a]++;
        in[b]++;
    }
    queue<int> q;
    FOR (i, 1, n + 1)
        if (in[i] == 1) q.push(i);

    while (n > 1) {
        int a = q.ft;
        q.pop();
        int b = q.ft;
        q.pop();
        cout << "? " << a << ' ' << b << endl;
        // cout.flush();
        int r;
        cin >> r;
        if (r == -1) return 0;
        if (r == a || r == b) {
            cout << "! " << r << endl;
            // cout.flush();
            return 0;
        }
        n -= 2;
        for (int u : adj[a])
            if (--in[u] == 1) q.push(u);
        for (int u : adj[b])
            if (--in[u] == 1) q.push(u);
    }
    int r = q.ft;
    cout << "! " << r << endl;
    // cout.flush();

    return 0;
}
