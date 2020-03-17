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

class FenwickTree {
   private:
    vi A;
    int n;
    int inline LSOne(int i) { return i & (-i); }
    int querry(int i) {
        int sum = 0;
        for (; i; i -= LSOne(i)) sum += A[i];
        return sum;
    }

   public:
    FenwickTree(int n) : A(n + 1, 0), n(n) {}
    void adjust(int i, int adjustBy) {
        for (; i <= n; i += LSOne(i)) A[i] += adjustBy;
    }
    int querry(int i, int j) { return querry(j) - querry(i - 1); }
};

typedef vector<ll> vll;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, m, k;
    cin >> n >> m >> k;
    vi a(n), b(m);
    F0R (i, n)
        cin >> a[i];
    F0R (i, m)
        cin >> b[i];

    vll divs;
    for (ll i = 1; i * i <= k; i++)
        if (k % i == 0) {
            divs.pb(i);
            if (k / i != i) divs.pb(k / i);
        }
    a.pb(0);
    b.pb(0);
    FenwickTree aa(n), bb(m);
    int cnt = 0;
    for (int i : a)
        if (i)
            aa.adjust(++cnt, 1);
        else
            cnt = 0;
    cnt = 0;
    for (int i : b)
        if (i)
            bb.adjust(++cnt, 1);
        else
            cnt = 0;
    ll sum = 0;
    for (int i : divs)
        if (i <= n && k / i <= m) sum += aa.querry(i, n) * bb.querry(k / i, m);

    cout << sum << endl;

    return 0;
}
