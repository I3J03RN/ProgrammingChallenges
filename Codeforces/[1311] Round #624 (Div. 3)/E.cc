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

int sums[5010];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    sums[0] = 0;
    F0R (i, 5000)
        sums[i + 1] = sums[i] + i + 1;

    int tcs;
    cin >> tcs;
    while (tcs--) {
        int n, d;
        cin >> n >> d;
        int maximum = sums[n - 1];
        int minimum = 0;
        for (int nodes = n, depth = 0; nodes;
             nodes = max(0, nodes - (1 << depth++)))
            minimum += min(nodes, 1 << depth) * depth;
        if (minimum > d || d > maximum) {
            cout << "NO" << endl;
            continue;
        }
        vi parent(n, -1), childs(n, 1);
        childs.bk = 0;
        set<ii> goodLeaves;
        goodLeaves.emplace(n - 1, n - 1);
        vi depth(n);
        iota(ALL(depth), 0);
        iota(ALL(parent), -1);
        int val = sums[n - 1];
        while (val > d) {
            auto [de, leave] = *goodLeaves.begin();
            goodLeaves.erase(goodLeaves.begin());
            int p = -1;
            if (depth[leave] > 1) F0R (i, n)
                    if (depth[i] == de - 2 && childs[i] < 2) p = i;
            if (p == -1) continue;
            if (--childs[parent[leave]] == 0)
                goodLeaves.emplace(depth[parent[leave]], parent[leave]);
            ++childs[p];
            parent[leave] = p;
            --depth[leave];
            val--;
            goodLeaves.emplace(de - 1, leave);
        }

        cout << "YES" << endl;
        FOR (i, 1, n)
            cout << parent[i] + 1 << ' ';
        cout << endl;
    }
    return 0;
}
