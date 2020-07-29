// this line is here for a reason
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
#define ft front
#define bk back
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

bool palin(const string& a, const string& b) {
    for (int l = 0, r = SZ(a) - 1; l < SZ(a); ++l, --r)
        if (a[l] != b[r]) return false;
    return true;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, m;
    cin >> n >> m;
    array<string, 110> strings;
    F0R (i, n)
        cin >> strings[i];

    vii pairs;
    bitset<110> foundPartner;
    F0R (i, n) {
        if (foundPartner[i]) continue;
        FOR (j, i + 1, n) {
            if (foundPartner[j]) continue;
            if (palin(strings[i], strings[j])) {
                foundPartner[i] = foundPartner[j] = true;
                pairs.eb(i, j);
                break;
            }
        }
    }

    int middle = -1;
    F0R (i, n) {
        if (!foundPartner[i]) {
            if (palin(strings[i], strings[i])) {
                middle = i;
                break;
            }
        }
    }

    cout << SZ(pairs) * 2 * m + (middle == -1 ? 0 : m) << endl;

    F0R (i, SZ(pairs))
        cout << strings[pairs[i].fi];

    if (middle != -1) cout << strings[middle];

    for (int i = SZ(pairs) - 1; i >= 0; --i) cout << strings[pairs[i].se];

    cout << endl;
    return 0;
}
