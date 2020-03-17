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

    int n;
    cin >> n;
    vi a(n), arr(n);
    F0R (i, n)
        cin >> a[i];

    int sol = 0;
    F0R (b, 25) {
        F0R (i, n)
            arr[i] = a[i] & ((1 << (b + 1)) - 1);
        sort(ALL(arr));
        ll numOnes = 0;
        F0R (i, n) {
            auto it1 =
                lower_bound(arr.begin() + i + 1, arr.end(), (1 << b) - arr[i]);
            auto it2 = upper_bound(it1, arr.end(), (1 << (b + 1)) - 1 - arr[i]);
            numOnes += distance(it1, it2);
            it1 =
                lower_bound(it2, arr.end(), (1 << (b + 1)) + (1 << b) - arr[i]);
            it2 = upper_bound(it1, arr.end(), (1 << (b + 2)) - 1 - arr[i]);
            numOnes += distance(it1, it2);
        }

        sol |= (numOnes & 1) << b;
    }
    cout << sol << endl;

    return 0;
}
