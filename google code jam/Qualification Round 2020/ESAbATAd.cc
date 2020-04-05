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
//#define endl '\n'
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

    int tcs, b;
    cin >> tcs >> b;
    while (tcs--) {
        int eq = -1, neq = -1;
        vi arr(b + 1, -1);
        int q = 0;
        int l = 1, r = b;
        while (1) {
            if (q > 1 && q % 10 == 0) {
                if (~eq && ~neq) {
                    int eqAns, neqAns;
                    cout << eq << endl;
                    cin >> eqAns;
                    cout << neq << endl;
                    cin >> neqAns;
                    bool cEq = eqAns != arr[eq];
                    bool cNeq = neqAns != arr[neq];
                    for (int ll = 1, rr = b; ll < rr; ++ll, --rr) {
                        if (arr[ll] == -1) continue;
                        if (arr[ll] == arr[rr] && cEq)
                            arr[ll] = arr[rr] = arr[ll] != 1;
                        if (arr[ll] != arr[rr] && cNeq) swap(arr[ll], arr[rr]);
                    }
                } else if (~eq) {
                    int eqAns;
                    cout << eq << endl;
                    cin >> eqAns;
                    cout << eq << endl;
                    cin >> eqAns;
                    bool cEq = eqAns != arr[eq];
                    for (int ll = 1, rr = b; ll < rr; ++ll, --rr) {
                        if (arr[ll] == -1) continue;
                        if (arr[ll] == arr[rr] && cEq)
                            arr[ll] = arr[rr] = arr[ll] != 1;
                    }
                } else {
                    int neqAns;
                    cout << neq << endl;
                    cin >> neqAns;
                    cout << neq << endl;
                    cin >> neqAns;
                    bool cNeq = neqAns != arr[neq];
                    for (int ll = 1, rr = b; ll < rr; ++ll, --rr) {
                        if (arr[ll] == -1) continue;
                        if (arr[ll] != arr[rr] && cNeq) swap(arr[ll], arr[rr]);
                    }
                }
                q += 2;
            }
            if (l >= r) break;
            cout << l << endl;
            cin >> arr[l];
            cout << r << endl;
            cin >> arr[r];
            // cerr << l << ' ' << arr[l] << endl;
            // cerr << r << ' ' << arr[r] << endl;
            if (arr[l] == arr[r] && eq == -1) eq = l;
            if (arr[l] != arr[r] && neq == -1) neq = l;
            l++;
            --r;
            q += 2;
        }
        FOR (i, 1, b + 1)
            cout << arr[i];
        cout << endl;
        char ok;
        cin >> ok;
        if (ok == 'N') return 0;
    }

    return 0;
}
