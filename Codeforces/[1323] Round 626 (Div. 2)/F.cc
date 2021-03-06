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

int l[2010], s[2010], c[4020];
int dp[4020][2010];

constexpr int impossible = 0x80808080;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, m;
    cin >> n >> m;
    F0R (i, n)
        cin >> l[i];
    F0R (i, n)
        cin >> s[i];
    FOR (i, 1, n + m + 1)
        cin >> c[i];

    vi candidates(n);
    iota(RALL(candidates), 0);
    // sort(RALL(candidates), [&](int a, int b) { return l[a] < l[b]; });
    memset(dp, 0x80, sizeof(dp));

    FOR (i, 1, n + m + 1)
        dp[i][0] = 0;

    for (int candidate : candidates) {
        R0F (count, n - 1) {
            int init = l[candidate];
            if (dp[init][count] != impossible)
                ckmax(dp[init][count + 1],
                      dp[init][count] + c[init] - s[candidate]);
            for (int lvl = init, cnt = count + 1; cnt > 1; cnt >>= 1, ++lvl) {
                if (dp[lvl][cnt] != impossible)
                    ckmax(dp[lvl + 1][cnt >> 1],
                          dp[lvl][cnt] + (cnt >> 1) * c[lvl + 1]);
            }
        }
    }

    int best = 0;
    FOR (i, 1, n + m + 1)
        FOR (j, 1, n + 1)
            ckmax(best, dp[i][j]);

    FOR (i, 1, n + m + 1) {
        cout << setw(3) << i << ": ";
        F0R (j, n + 1)
            cout << setw(15) << dp[i][j];
        cout << endl;
    }
    cout << best << endl;

    return 0;
}
