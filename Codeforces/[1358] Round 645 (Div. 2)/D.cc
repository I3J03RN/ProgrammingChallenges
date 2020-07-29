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

ll gauss(ll n) { return n * (n + 1) / 2; }

void solve() {
    int n;
    ll x;
    cin >> n >> x;
    vector<ll> days(n);
    F0R (i, n)
        cin >> days[i];
    days.insert(days.end(), ALL(days));
    vector<ll> pred(days);
    vector<ll> preV(2 * n);
    preV[0] = gauss(days[0]);
    FOR (i, 1, 2 * n)
        preV[i] = preV[i - 1] + gauss(days[i]);
    FOR (i, 1, 2 * n)
        pred[i] += pred[i - 1];
    ll best = 0;
    dout << dvar(pred) << endl << dvar(preV) << endl;

    FOR (i, n, 2 * n) {
        int j = lower_bound(ALL(pred), pred[i] - x + 1) - pred.begin();
        dout << dvar(i) << dvar(j) << endl;
        ll val;
        if (j == i) {
            val = gauss(days[i]) - gauss(days[i] - x);
        } else {
            ll toomuch = pred[i] - (j ? pred[j - 1] : 0) - x;
            dout << dvar(toomuch) << endl;
            val = preV[i] - (j ? preV[j - 1] : 0) - gauss(toomuch);
        }
        dout << dvar(val) << endl;
        ckmax(best, val);
    }

    cout << best << endl;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    // int tt;
    // cin >> tt;
    // FOR (t, 1, tt + 1) {
    // cout << "Case #" << t << ": ";
    solve();
    // }

    return 0;
}
