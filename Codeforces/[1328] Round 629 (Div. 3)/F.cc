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

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    ll n, k;
    cin >> n >> k;
    vi a(n);
    F0R (i, n)
        cin >> a[i];

    sort(ALL(a));

    for (int val = a[0], cnt = 1, i = 1; i < n; ++i) {
        if (cnt == k) {
            cout << 0 << endl;
            return 0;
        }
        if (a[i] == val)
            cnt++;
        else {
            val = a[i];
            cnt = 1;
        }
    }

    vector<tuple<ll, ll, ll, ll>> prefix(n), suffix(n);
    prefix[0] = mt(a[0], 1, 0, 0);
    FOR (i, 1, n) {
        auto [val, amount, fr, cost] = prefix[i - 1];
        prefix[i] = mt(a[i], amount + 1, a[i] != val ? amount : fr,
                       cost + (a[i] - val) * amount);
    }
    suffix[n - 1] = mt(a[n - 1], 1, 0, 0);
    R0F (i, n - 2) {
        auto [val, amount, fr, cost] = suffix[i + 1];
        suffix[i] = mt(a[i], amount + 1, a[i] != val ? amount : fr,
                       cost + (val - a[i]) * amount);
    }

    // cout << "prefix: " << endl;
    // for (auto [val, amount, fr, cost] : prefix)
    //     cout << val << ", " << amount << ", " << fr << ", " << cost << endl;

    // cout << "suffix: " << endl;
    // for (auto [val, amount, fr, cost] : suffix)
    //     cout << val << ", " << amount << ", " << fr << ", " << cost << endl;

    ll best = numeric_limits<ll>::max();
    for (int l = 0, r = 0; l < n; ++l) {
        auto [val, amount, fr, cost] = prefix[l];
        if (amount >= k) ckmin(best, cost - min(amount - k, fr));

        while (r + 1 < n && get<0>(suffix[r + 1]) == val &&
               get<1>(suffix[r + 1]) + amount >= k)
            ++r;
        // cout << "paired: " << l << ' ' << r << endl;
        amount += get<1>(suffix[r]);
        ckmin(amount, n);
        fr += get<2>(suffix[r]);
        cost += get<3>(suffix[r]);
        // cout << cost - min(fr, amount - k) << endl;
        ckmin(best, cost - min(fr, amount - k));
    }
    for (int r = n - 1, l = n - 1; ~r; --r) {
        auto [val, amount, fr, cost] = suffix[r];
        if (amount >= k) ckmin(best, cost - min(amount - k, fr));
        while (l > 0 && get<0>(prefix[l - 1]) == val &&
               get<1>(prefix[l - 1]) + amount >= k)
            --l;
        // cout << "paired: " << l << ' ' << r << endl;
        amount += get<1>(prefix[l]);
        ckmin(amount, n);
        fr += get<2>(prefix[l]);
        cost += get<3>(prefix[l]);
        // cout << cost - min(fr, amount - k) << endl;
        ckmin(best, cost - min(fr, amount - k));
    }

    cout << best << endl;

    return 0;
}
