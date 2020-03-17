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

int sol[100] = {0};
bool possible = true;

ll u, v;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> u >> v;
    if (u > v || ((u ^ v) & 1)) {
        cout << -1 << endl;
        return 0;
    }
    if (u == v) {
        if (u == 0)
            cout << 0 << endl;
        else
            cout << 1 << endl << u << endl;
        return 0;
    }
    ll a, b;
    a = b = (v - u) >> 1;
    int bit = 0;
    bool two = true;
    while (u >> bit) {
        ll c = (u >> bit) & 1;
        if (c) {
            if ((a >> bit) & 1) {
                two = false;
                break;
            } else
                a |= 1LL << bit;
        }
        ++bit;
    }
    if (two) {
        cout << 2 << endl;
        cout << a << ' ' << b << endl;
    } else {
        cout << 3 << endl;
        ll x = (v - u) >> 1;
        cout << u << ' ' << x << ' ' << x << endl;
    }
    return 0;
}
