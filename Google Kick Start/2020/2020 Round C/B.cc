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

void solve() {
    int R, C;
    cin >> R >> C;
    vector<vector<char>> field(R, vector<char>(C));
    F0R (r, R)
        F0R (c, C)
            cin >> field[r][c];
    vector<bool> placed(26, true);
    F0R (r, R)
        F0R (c, C)
            placed[field[r][c] - 'A'] = false;
    vector<set<char>> pre(26);
    FOR (r, 1, R)
        F0R (c, C)
            if (field[r][c] != field[r - 1][c])
                pre[field[r][c] - 'A'].insert(field[r - 1][c]);

    dout << dvar(pre) << endl;
    string sol;

    while (count(ALL(placed), false)) {
        char next = 0;
        F0R (i, 26) {
            if (placed[i]) continue;
            if (pre[i].empty()) {
                next = 'A' + i;
                placed[i] = true;
                break;
            }
        }
        dout << dvar(next) << endl;
        if (!next) {
            cout << -1 << endl;
            return;
        }

        sol += next;
        for (auto& s : pre) s.erase(next);
    }

    reverse(ALL(sol));
    cout << sol << endl;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int tt;
    cin >> tt;
    FOR (t, 1, tt + 1) {
        cout << "Case #" << t << ": ";
        solve();
    }

    return 0;
}
