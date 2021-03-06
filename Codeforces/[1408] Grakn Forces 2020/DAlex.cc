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
#define eb emplace_back
#define pb push_back
#define mp make_pair
#define mt make_tuple
#define endl '\n'
#define ALL(x) (x).begin(), (x).end()
#define RALL(x) (x).rbegin(), (x).rend()
#define SZ(x) (int)(x).size()
#define FOR(a, b, c) for (auto a = (b); (a) < (c); ++(a))
#define F0R(a, b) FOR(a, 0, (b))
template <class T>
bool ckmin(T& a, const T& b) {
    return a > b ? a = b, true : false;
}
template <class T>
bool ckmax(T& a, const T& b) {
    return a < b ? a = b, true : false;
}
#ifndef DEBUG
#define DEBUG 0
#endif
#define dout \
    if (DEBUG) cerr
#define dvar(...) " [" << #__VA_ARGS__ ": " << mt(__VA_ARGS__) << "] "
template <typename T>
struct IsC {
    template <typename C>
    static char test(typename C::const_iterator*);
    template <typename C>
    static int test(...);
    static const bool value = sizeof(test<T>(0)) == sizeof(char);
};
template <>
struct IsC<string> {
    static const bool value = false;
};
template <typename C>
typename enable_if<IsC<C>::value, ostream&>::type operator<<(ostream&,
                                                             const C&);
template <typename T1, typename T2>
ostream& operator<<(ostream&, const pair<T1, T2>&);
template <typename... T>
using TS = tuple_size<tuple<T...>>;
template <size_t idx, typename... T>
typename enable_if<TS<T...>::value == idx + 1, ostream&>::type operator<<(
    ostream& o, const tuple<T...>& t) {
    return o << ", " << get<idx>(t) << ')';
}
template <size_t idx, typename... T>
typename enable_if<0 < idx && idx + 1 < TS<T...>::value, ostream&>::type
operator<<(ostream& o, const tuple<T...>& t) {
    return operator<<<idx + 1>(o << ", " << get<idx>(t), t);
}
template <size_t idx = 0, typename... T>
typename enable_if<1 < TS<T...>::value && !idx, ostream&>::type operator<<(
    ostream& o, const tuple<T...>& t) {
    return operator<<<idx + 1>(o << '(' << get<idx>(t), t);
}
template <typename T>
ostream& operator<<(ostream& o, const tuple<T>& t) {
    return o << get<0>(t);
}
template <typename T1, typename T2>
ostream& operator<<(ostream& o, const pair<T1, T2>& p) {
    return o << mt(p.fi, p.se);
}
template <typename C>
typename enable_if<IsC<C>::value, ostream&>::type operator<<(ostream& o,
                                                             const C& c) {
    o << '[';
    for (auto it = c.cbegin(); it != c.cend(); ++it)
        o << *it << (next(it) != c.cend() ? ", " : "");
    return o << ']';
}
template <typename T>
void tprint(vector<vector<T>>& v, size_t width = 0, ostream& o = cerr) {
    if (!DEBUG) return;
    for (const auto& vv : v) {
        for (const auto& i : vv) o << setw(width) << i;
        o << endl;
    }
}

void solve() {
    int n, m;
    cin >> n >> m;

    vii a(n);
    F0R(i, n)
        cin >> a[i].fi >> a[i].se;

    vii b(m);
    F0R(i, m) {
        cin >> b[i].fi >> b[i].se;
    }

    sort(ALL(b));

    vi height(b[m - 1].fi + 5);
    for(int i = m - 1; ~i; --i) {
        auto [x, h] = b[i];

        while(i - 1 >= 0 && b[i].se == b[i - 1].se) i--;

        int xLeft = i ? b[i - 1].fi : -1;
        dout << dvar(h, xLeft, x) << endl;
        FOR(j, xLeft + 1, x + 1)
            height[j] = h + 1;
    }
    dout << dvar(height) << endl;

    int res = 1e9;
    F0R(i, 1e5 + 1) {
        //int moveRight = i ? b[i - 1].fi + 1 : 0;
        int moveRight = i;
        int currMax = 0;
        dout << dvar(moveRight) << endl;
        F0R(j, n) {
            int newX = a[j].fi + moveRight;
            int h = newX < SZ(height) ? height[newX] : 0;

            dout << dvar(a[j], newX, h, moveRight + max(0, h - a[j].se)) << endl;

            ckmax(currMax, moveRight + max(0, h - a[j].se));
        }
        dout << dvar(currMax) << endl;
        ckmin(res, currMax);
    }

    cout << res << endl;
}

int main() {
    cin.tie(0);
    ios_base::sync_with_stdio(0);

    int tc = 1;
    FOR(i, 1, tc + 1) {
        // cout << "Case #" << i << ": ";
        solve();
    }
}


