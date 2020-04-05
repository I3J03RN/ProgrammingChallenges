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

class SegmentTree {
   private:
    int n;
    vi value, up;
    int inline left(int p) { return p << 1; }
    int inline right(int p) { return (p << 1) + 1; }

    int build(const vi& a, int p, int L, int R) {
        if (L == R) {
            return value[p] = a[L];
        } else {
            value[p] = max(build(a, left(p), L, (R + L) / 2),
                           build(a, right(p), (R + L) / 2 + 1, R));
            return value[p];
        }
    }
    int rmq(int p, int L, int R, int i, int j) {
        if (i > R || j < L) return numeric_limits<int>::min();
        if (i <= L && R <= j) return value[p];
        push(p, L, R);
        return max(rmq(left(p), L, (L + R) / 2, i, j),
                   rmq(right(p), (L + R) / 2 + 1, R, i, j));
    }
    int add(int p, int L, int R, int i, int j, int val) {
        if (i > R || j < L) return value[p];
        if (L == R) return value[p] += val;
        if (i <= L && R <= j) {
            up[p] += val;
            return value[p] += val;
        }
        push(p, L, R);
        return value[p] = max(add(left(p), L, (L + R) / 2, i, j, val),
                              add(right(p), (L + R) / 2 + 1, R, i, j, val));
    }
    void push(int p, int L, int R) {
        if (up[p]) {
            add(left(p), L, (L + R) / 2, L, R, up[p]);
            add(right(p), (L + R) / 2 + 1, R, L, R, up[p]);
            up[p] = 0;
        }
    }

   public:
    SegmentTree(int n) : n(n), value(n * 4, 0), up(n * 4, 0) {}
    SegmentTree(const vi& a) : n(SZ(a)), value(SZ(a) * 4), up(SZ(a) * 4) {
        build(a, 1, 0, SZ(a) - 1);
    }
    int rmq(int i, int j) { return rmq(1, 0, n - 1, i, j); }
    void add(int i, int j, int val) { add(1, 0, n - 1, i, j, val); }
    int size() { return n; }
};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;

    vi pos(n + 1), a(n);
    F0R (i, n) {
        cin >> a[i];
        pos[a[i]] = i;
    }
    SegmentTree st(n);
    int ans = n;
    st.add(0, pos[ans], 1);
    F0R (i, n) {
        cout << ans << ' ';
        int q;
        cin >> q;
        st.add(0, q - 1, -1);
        while (st.rmq(0, n - 1) <= 0) st.add(0, pos[--ans], 1);
    }
    cout << endl;
}
