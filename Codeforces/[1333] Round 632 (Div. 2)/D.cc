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
#define SZ(x) (x).size()
#define ft front()
#define bk back()
#define endl '\n'
#define FOR(a, b, c) for (auto(a) = (b); (a) < (c); ++(a))
#define ROF(a, b, c) for (auto(a) = (b); (a) > (c); --(a))
#define F0R(a, b) FOR ((a), 0, (b))
#define R0F(a, b) ROF ((a), (b), -1)
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

    int n, k;
    cin >> n >> k;
    string start;
    cin >> start;
    assert(n == SZ(start));
    ll maxSecs = 0, minSecs = 0;
    bitset<3010> left;
    F0R (i, n)
        left[i] = start[i] == 'L';
    vector<ll> level;
    while (1) {
        ll last = maxSecs;
        F0R (i, n - 1) {
            if (!left[i] && left[i + 1]) {
                left[i] = true;
                left[i + 1] = false;
                ++i;
                ++maxSecs;
            }
        }
        if (maxSecs == last) break;
        level.pb(maxSecs - last);
        ++minSecs;
    }
    if (minSecs > k || maxSecs < k) {
        cout << -1 << endl;
        return 0;
    }
    // for (auto l : level) cout << l << endl;
    // cout <<
    // "------------------------------------------------------------------"
    //         "----"
    //      << endl;

    F0R (i, n)
        left[i] = start[i] == 'L';

    vector<ll> cum(SZ(level));
    cum.bk = level.bk;
    for (int i = SZ(level) - 2; ~i; --i) cum[i] = cum[i + 1] + level[i];
    cum.pb(0);

    // for (auto l : cum) cout << l << endl;
    // cout <<
    // "------------------------------------------------------------------"
    //         "----"
    //      << endl;
    // for (auto l : level) cout << l << endl;
    // for (auto i : cum) cout << i << endl;

    // multiple
    F0R (i, SZ(level)) {
        ll now;
        if (k - 1 > cum[i + 1]) {
            now = level[i] - (k - 1 - cum[i + 1]);
        } else
            now = level[i];

        assert(now > 0);
        cout << now << ' ';
        for (int j = 0, cnt = 0; cnt < now; ++j) {
            if (!left[j] && left[j + 1]) {
                left[j] = true;
                left[j + 1] = false;
                cout << j + 1 << ' ';
                ++j;
                ++cnt;
            }
        }
        cout << endl;
        --k;
        if (now < level[i]) break;
    }
    // one at a time
    int p = 0;
    while (k--) {
        while (1) {
            if (!left[p] && left[p + 1]) {
                left[p] = true;
                left[p + 1] = false;
                cout << 1 << ' ' << p + 1 << endl;
                p = (p + 2) % (n - 1);
                break;
            }
            p = (p + 1) % (n - 1);
        }
    }
    // F0R (i, n)
    //     cout << (left[i] ? 'L' : 'R');
    // cout << endl;
    return 0;
}
