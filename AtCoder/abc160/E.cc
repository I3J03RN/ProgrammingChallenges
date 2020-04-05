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

typedef vector<ll> vll;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int a, b, c, x, y;
    cin >> x >> y >> a >> b >> c;

    vll p(a), q(b), r(c);
    F0R (i, a)
        cin >> p[i];
    F0R (i, b)
        cin >> q[i];
    F0R (i, c)
        cin >> r[i];

    sort(ALL(p));
    sort(ALL(q));
    sort(ALL(r));

    vll solution(x + y);
    F0R (i, x)
        solution[i] = p[a - x + i];
    F0R (i, y)
        solution[x + i] = q[b - y + i];
    sort(ALL(solution));
    for (int i = x + y - 2; i >= 0; --i) solution[i] += solution[i + 1];
    for (int i = c - 2; i >= 0; --i) r[i] += r[i + 1];
    ll sum = solution[0];
    F0R (i, min(c, x + y))
        ckmax(sum, r[c - i - 1] + solution[i + 1]);

    // for (int pc = c - 1, ps = x + y - 1, end = 0;
    //      pc >= max(0, c - (x + y)) && end <= ps;) {
    //     if (solution[ps] < r[pc])
    //         sum += r[pc--] - solution[end++];
    //     else
    //         --ps;
    // }

    cout << sum << endl;

    return 0;
}
