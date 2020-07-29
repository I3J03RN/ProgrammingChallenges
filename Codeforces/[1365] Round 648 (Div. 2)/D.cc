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
#define SZ(x) (int)(x).size()
#define endl '\n'
#define FOR(a, b, c) for (auto(a) = (b); (a) < (c); ++(a))
#define ROF(a, b, c) for (auto(a) = (b); (a) > (c); --(a))
#define F0R(a, b) FOR ((a), 0, (b))
#define R0F(a, b) ROF ((a), (b), -1)
#define CEIL(a, b) ((a) + (b)-1) / (b)
#define SET(a, b) memset((a), (b), sizeof(a))
template <class t>
bool ckmin(t& a, const t& b) {
    return a > b ? a = b, true : false;
}
template <class t>
bool ckmax(t& a, const t& b) {
    return a < b ? a = b, true : false;
}
#ifndef DEBUG
#define DEBUG 0
#endif
#define dout \
    if (DEBUG) std::cerr
#define dvar(...) " [" << #__VA_ARGS__ ": " << (__VA_ARGS__) << "] "
template <class a, class b>
ostream& operator<<(ostream& o, const pair<a, b>& p);
template <class T>
struct IsC {
    template <class C>
    static char test(typename C::const_iterator*);
    template <class C>
    static int test(...);
    static const bool value = sizeof(test<T>(0)) == sizeof(char);
};
template <>
struct IsC<string> {
    static const bool value = false;
};
template <class C>
typename enable_if<IsC<C>::value, ostream&>::type operator<<(ostream& o,
                                                             const C& c) {
    o << '[';
    for (auto it = c.begin(); it != c.end();)
        o << *it << (++it != c.end() ? ", " : "");
    return o << ']';
}
template <class a, class b>
ostream& operator<<(ostream& o, const pair<a, b>& p) {
    return o << '(' << p.fi << ", " << p.se << ')';
}

array<int, 4> dr{0, 0, -1, 1}, dc{1, -1, 0, 0};

int n, m;
vector<string> field;

bool ok(int r, int c) {
    return 0 <= r && r < n && 0 <= c && c < m;
}

int dfs (int r, int c) {
    int res = 0;
    if (field[r][c] == 'G') ++res;
    field[r][c] = '#';
    F0R (i, 4) {
        int rr = r + dr[i], cc = c + dc[i];
        if (ok(rr, cc) && field[rr][cc] != '#') res += dfs(rr, cc);
    }
    return res;
}

void solve() {
    cin >> n >> m;
    field.clear();
    field.resize(n);
    F0R (i, n) cin >> field[i];
    bool pos = 1;
    int goods = 0;
    F0R (r, n) {
        F0R (c, m) {
            if (field[r][c] == 'B') {
                F0R (i, 4) {
                    int rr = r + dr[i], cc = c + dc[i];
                    if (ok(rr, cc)) {
                        if (field[rr][cc] == 'G') {
                            pos = 0;
                        } else if (field[rr][cc] == '.') {
                            field[rr][cc] = '#';
                        }
                    }
                }
            } else if (field[r][c] == 'G') {
                ++goods;
            }
        }
    }
    if (pos) {
        pos = goods == (field[n - 1][m - 1] == '#' ? 0 : dfs(n - 1, m - 1));
    }
    cout << (pos ? "Yes" : "No") << endl;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int tt;
    cin >> tt;
    FOR (t, 1, tt + 1) {
	// cout << "Case #" << t << ": ";
	solve();
    }

    return 0;
}
