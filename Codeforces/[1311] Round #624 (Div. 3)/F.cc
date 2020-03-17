#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define int ll
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

class FenwickTree {
   private:
    vi A;
    int n;
    int inline LSOne(int i) { return i & (-i); }
    int query(int i) {
        int sum = 0;
        for (; i; i -= LSOne(i)) sum += A[i];
        return sum;
    }

   public:
    FenwickTree(int n) : A(n + 1, 0), n(n) {}
    void adjust(int i, int adjustBy) {
        for (; i <= n; i += LSOne(i)) A[i] += adjustBy;
    }
    int query(int i, int j) { return query(j) - query(i - 1); }
};

int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;

    FenwickTree cnt(n), dist(n);
    vi x(n), v(n), is(n), tmp(n);
    F0R (i, n)
        cin >> x[i], x[i]--;

    F0R (i, n)
        cin >> v[i];
    iota(ALL(is), 0);
    iota(ALL(tmp), 0);
    sort(ALL(is), [&](int a, int b) {
        if (v[a] == v[b]) return x[a] < x[b];
        return v[a] < v[b];
    });
    sort(ALL(tmp), [&](int a, int b) { return x[a] < x[b]; });
    vi pos(n);
    F0R (i, n) { pos[tmp[i]] = i; }

    int sum = 0;
    for (auto i : is) {
        sum += cnt.query(1, pos[i] + 1) * x[i] - dist.query(1, pos[i] + 1);
        cnt.adjust(pos[i] + 1, 1);
        dist.adjust(pos[i] + 1, x[i]);
    }
    cout << sum << endl;

    return 0;
}
