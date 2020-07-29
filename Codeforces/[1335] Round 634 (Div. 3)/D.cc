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

int main() {
    ios_base::sync_with_stdio(0);
    cout.tie(0);

    int tt;
    cin >> tt;
    while (tt--) {
        vvi s(9, vi(9, 0));
        F0R (i, 9)
            F0R (j, 9) {
                char c;
                cin >> c;
                s[i][j] = c - '1';
            }
        F0R (offset, 3) {
            F0R (i, 3) {
                s[offset + i * 3][offset * 3 + i] =
                    (s[offset + i * 3][offset * 3 + i] + 1) % 9;
            }
        }
        F0R (i, 9) {
            F0R (j, 9)
                cout << s[i][j] + 1;
            cout << endl;
        }
    }

    return 0;
}
