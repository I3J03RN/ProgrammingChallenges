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

    int tcs;
    cin >> tcs;
    while (tcs--) {
        int n;
        cin >> n;
        vi a(n), b(n);
        F0R (i, n)
            cin >> a[i];
        F0R (i, n)
            cin >> b[i];
        bool incp = false, decp = false;
        bool ok = true;
        F0R (i, n) {
            if (b[i] > a[i] && !incp) {
                ok = false;
                break;
            }
            if (b[i] < a[i] && !decp) {
                ok = false;
                break;
            }
            if (a[i] > 0) incp = true;
            if (a[i] < 0) decp = true;
        }
        cout << (ok ? "YES" : "NO") << endl;
    }

    return 0;
}
