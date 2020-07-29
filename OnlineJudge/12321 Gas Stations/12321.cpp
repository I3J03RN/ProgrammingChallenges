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
#define ft front
#define bk back
#define ins insert
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

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    vii stations;
    stations.reserve(10e4);

    int L, G;
    while (cin >> L >> G, L) {
        stations.clear();
        while (G--) {
            int coord, radius;
            cin >> coord >> radius;
            stations.pb(mp(coord, radius));
        }
        sort(ALL(stations),
             [](ii a, ii b) -> bool { return a.fi - a.se < b.fi - b.se; });
        int lastr = 0;
        int furthest = 0;
        int trash = 0;
        for (int i = 0; i < SZ(stations);) {
            auto& g = stations[i];
            // cout << g.fi << ", " << g.se << ": " << lastr << ", " << furthest
            //      << endl;
            if (lastr >= L) {
                trash++;
                i++;
            } else if (g.fi - g.se <= lastr) {
                if (furthest < g.fi + g.se) {
                    if (furthest != lastr) trash++;
                    furthest = g.fi + g.se;
                } else
                    trash++;
                i++;
            } else {
                if (furthest != lastr) {
                    lastr = furthest;
                    furthest = lastr;
                } else {
                    trash = -1;
                    break;
                }
            }
        }
        if (furthest < L) trash = -1;
        cout << trash << '\n';
    }

    return 0;
}
