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

    int n, k, c;
    string s;
    cin >> n >> k >> c >> s;
    vi maxWorkDaysTo(n);
    maxWorkDaysTo[0] = 0;
    FOR (i, 1, n)
        maxWorkDaysTo[i] = max(
            maxWorkDaysTo[i - 1],
            i - 1 - c >= 0 ? maxWorkDaysTo[i - 1 - c] + (s[i - 1 - c] == 'o')
                           : 0);
    for (int i : maxWorkDaysTo) cout << i << endl;
    cout << "---------------" << endl;
    vi possibleWorkDays(n);
    possibleWorkDays[n - 1] = s[n - 1] == 'o';
    R0F (i, n - 2) {
        possibleWorkDays[i] = possibleWorkDays[i + 1];
        if (s[i] == 'o')
            ckmax(possibleWorkDays[i],
                  (i + 1 + c < n ? possibleWorkDays[i + 1 + c] : 0) + 1);
    }
    for (int i : possibleWorkDays) {
        cout << i << endl;
    }
    cout << "---------------" << endl;
    F0R (i, n) {
        if (s[i] == 'o' &&
            maxWorkDaysTo[i] + (i + 1 == n ? 0 : possibleWorkDays[i + 1]) < k)
            cout << i + 1 << endl;
    }

    return 0;
}
