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
#define ft front()
#define bk back()
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

array<int, 4> rd = {1, 0, -1, 0};
array<int, 4> cd = {0, 1, 0, -1};

int rows, columns;
vector<vector<bool>> must;

bool ok(int r, int c) { return r >= 0 && c >= 0 && r < rows && c < columns; }
void dfs(int r = 0, int c = 0) {
    must[r][c] = false;
    F0R (i, 4) {
        int rr = r + rd[i];
        int cc = c + cd[i];
        if (ok(rr, cc) && must[rr][cc]) {
            dfs(rr, cc);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> rows >> columns;

    must.assign(rows, vector<bool>(columns));
    F0R (i, rows)
        F0R (j, columns) {
            char c;
            cin >> c;
            must[i][j] = c == '#';
        }
    bool emptyrow = false;
    bool emptycolumn = false;
    F0R (i, rows) {
        bool found = false;
        bool last = false;
        F0R (j, columns) {
            if (must[i][j]) {
                if (found && !last) {
                    cout << -1 << endl;
                    return 0;
                }
                found = true;
            }
            last = must[i][j];
        }
        if (!found) emptyrow = true;
    }
    F0R (j, columns) {
        bool found = false;
        bool last = false;
        F0R (i, rows) {
            if (must[i][j]) {
                if (found && !last) {
                    cout << -1 << endl;
                    return 0;
                }
                found = true;
            }
            last = must[i][j];
        }
        if (!found) emptycolumn = true;
    }
    if (emptycolumn != emptyrow) {
        cout << -1 << endl;
        return 0;
    }

    int cnt = 0;
    F0R (i, rows)
        F0R (j, columns)
            if (must[i][j]) {
                ++cnt;
                dfs(i, j);
            }

    cout << cnt << endl;

    return 0;
}
