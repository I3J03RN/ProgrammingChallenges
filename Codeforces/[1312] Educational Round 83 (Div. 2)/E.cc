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

constexpr int N = 510;

int dp[N][N];
int best[N];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;
    vi a(n);
    F0R (i, n)
        cin >> dp[i][i];

    F0R (r, n) {
        R0F (l, r - 1) {
            dp[l][r] = -1;
            FOR (k, l, r)
                if (~dp[l][k] && dp[l][k] == dp[k + 1][r])
                    dp[l][r] = dp[l][k] + 1;
        }
    }
    // F0R (l, n) {
    //     F0R (r, n)
    //         cout << setw(3) << dp[l][r];
    //     cout << endl;
    // }
    best[0] = 1;
    FOR (r, 1, n) {
        best[r] = n + 1;
        F0R (l, r + 1)
            if (~dp[l][r]) ckmin(best[r], best[l - 1] + 1);
    }

    cout << best[n - 1] << endl;
    return 0;
}
