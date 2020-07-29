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

void solve() {
    ll x, y;
    cin >> x >> y;
    ll xx = abs(x);
    ll yy = abs(y);
    string out = "";
    while (xx || yy) {
        dout << xx << ' ' << yy << endl;
        if ((xx & 1) == (yy & 1)) {
            out = "IMPOSSIBLE";
            break;
        }
        if (xx & 1) {
            if ((xx & 2) == (yy & 2) && (xx != 1 || yy > 1)) {
                out += x > 0 ? 'W' : 'E';
                ++xx;
            } else {
                out += x > 0 ? 'E' : 'W';
            }
        } else {
            if ((xx & 2) == (yy & 2) && (yy != 1 || xx > 1)) {
                out += y > 0 ? 'S' : 'N';
                ++yy;
            } else {
                out += y > 0 ? 'N' : 'S';
            }
        }
        xx >>= 1;
        yy >>= 1;
    }
    cout << out << endl;
}

int main() {
    ios_base::sync_with_stdio(0);
    cout.tie(0);

    int tt;
    cin >> tt;
    FOR (t, 1, tt + 1) {
        cout << "Case #" << t << ": ";
        solve();
    }

    return 0;
}
