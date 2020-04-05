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

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, m;
    cin >> n >> m;
    vi l(m);
    F0R (i, m)
        cin >> l[i];

    vi neededSpace(m);
    neededSpace.bk = l.bk;
    for (int i = m - 2; ~i; --i)
        neededSpace[i] = max(neededSpace[i + 1] + 1, l[i]);

    // for (int i : neededSpace) cout << i << endl;

    if (neededSpace[0] > n) {
        cout << -1 << endl;
        return 0;
    }

    vi place(m);
    int coloredUntil = -1;
    F0R (i, m) {
        place[i] = min(coloredUntil + 1, n - neededSpace[i]);
        coloredUntil = place[i] + l[i] - 1;
        // cout << place[i] << ' ' << coloredUntil << endl;
    }
    if (coloredUntil == n - 1) {
        for (int i : place) cout << i + 1 << ' ';
        cout << endl;
    } else
        cout << -1 << endl;

    return 0;
}
