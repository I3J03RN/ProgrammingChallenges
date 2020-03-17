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

int good[2010][2010];

int goodH[2010];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, h, l, r;
    cin >> n >> h >> l >> r;
    F0R (i, n + 1)
        F0R (j, h + 1)
            good[i][j] = -1;

    memset(goodH, 0, sizeof(goodH));
    FOR (i, l, r + 1)
        goodH[i] = 1;

    int a0;
    cin >> a0;
    good[0][a0] = goodH[a0];
    good[0][a0 - 1] = goodH[a0 - 1];

    FOR (i, 1, n) {
        int a;
        cin >> a;
        F0R (hour, h) {
            if (good[i - 1][(hour - a + h) % h] != -1)
                ckmax(good[i][hour],
                      good[i - 1][(hour - a + h) % h] + goodH[hour]);
            if (good[i - 1][(hour - a + 1 + h) % h] != -1)
                ckmax(good[i][hour],
                      good[i - 1][(hour - a + 1 + h) % h] + goodH[hour]);
        }
    }
    // F0R (hour, h) {
    //     cout << setw(3) << hour;
    //     F0R (i, n) { cout << setw(3) << good[i][hour]; }
    //     cout << endl;
    // }
    int best = 0;
    F0R (i, h)
        ckmax(best, good[n - 1][i]);
    cout << best << endl;

    return 0;
}
