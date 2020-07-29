#include <bits/stdc++.h>
#pragma GCC optimize("Ofast,unroll-loops,no-stack-protector,fast-math")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
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
int constexpr maxN = 2e5 + 1;
int pre[201][maxN];
int as[maxN];

int max_equal(int a, int b) {
    if (b < a) return 0;
    int best = 0;
    FOR (i, 1, 201)
        ckmax(best, pre[i][b] - (a > 0 ? pre[i][a - 1] : 0));
    return best;
}

int main() {
    ios_base::sync_with_stdio(0);
    cout.tie(0);

    int tt;
    cin >> tt;
    while (tt--) {
        int n;
        cin >> n;
        F0R (i, n)
            cin >> as[i];
        FOR (a, 1, 201)
            pre[a][0] = as[0] == a;
        FOR (i, 1, n)
            FOR (a, 1, 201)
                pre[a][i] = pre[a][i - 1] + (as[i] == a);
        int best = 0;
        FOR (a, 1, 201) {
            int cnt = 2;
            int l = 0, r = n - 1;
            while (1) {
                while (l < n && as[l] != a) ++l;
                while (r >= 0 && as[r] != a) --r;
                if (r < l) break;
                ckmax(best, cnt + max_equal(l + 1, r - 1) - (l == r));

                cnt += 2;
                ++l;
                --r;
            }
        }

        cout << best << endl;
    }

    return 0;
}
