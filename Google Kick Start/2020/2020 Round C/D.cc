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
#define SZ(x) (int)(x).size()
#define ft front()
#define bk back()
#define endl '\n'
#define FOR(a, b, c) for (auto(a) = (b); (a) < (c); ++(a))
#define ROF(a, b, c) for (auto(a) = (b); (a) > (c); --(a))
#define F0R(a, b) FOR ((a), 0, (b))
#define R0F(a, b) ROF ((a), (b), -1)
#define CEIL(a, b) ((a) + (b)-1) / (b)
#define SET(a, b) memset((a), (b), sizeof(a))
template <class t>
bool ckmin(t& a, const t& b) {
    return a > b ? a = b, true : false;
}
template <class t>
bool ckmax(t& a, const t& b) {
    return a < b ? a = b, true : false;
}
#ifndef DEBUG
#define DEBUG 0
#endif
#define dout \
    if (DEBUG) std::cerr
#define dvar(...) " [" << #__VA_ARGS__ ": " << (__VA_ARGS__) << "] "
template <class a, class b>
ostream& operator<<(ostream& o, const pair<a, b>& p);
template <class T>
struct IsC {
    template <class C>
    static char test(typename C::const_iterator*);
    template <class C>
    static int test(...);
    static const bool value = sizeof(test<T>(0)) == sizeof(char);
};
template <>
struct IsC<string> {
    static const bool value = false;
};
template <class C>
typename enable_if<IsC<C>::value, ostream&>::type operator<<(ostream& o,
                                                             const C& c) {
    o << '[';
    for (auto it = c.begin(); it != c.end();)
        o << *it << (++it != c.end() ? ", " : "");
    return o << ']';
}
template <class a, class b>
ostream& operator<<(ostream& o, const pair<a, b>& p) {
    return o << '(' << p.fi << ", " << p.se << ')';
}

using pll = pair<ll, ll>;

vector<ll> a;

class SegmentTree {
   private:
    int n;
    vector<ll> value, sum;
    int inline left(int p) { return p << 1; }
    int inline right(int p) { return (p << 1) + 1; }
    pll combine(pll l, int lenl, pll r) {
        if (lenl & 1) {
            return {l.fi - lenl * r.se - r.fi, l.se - r.se};
        }
        return {l.fi + lenl * r.se + r.fi, l.se + r.se};
    }
    pll build(int p, int L, int R) {
        if (L == R) {
            return {value[p] = a[L], sum[p] = a[L]};
        } else {
            pll out =
                combine(build(left(p), L, (R + L) / 2), (R + L) / 2 - L + 1,
                        build(right(p), (R + L) / 2 + 1, R));
            return {value[p] = out.fi, sum[p] = out.se};
        }
    }
    pll query(int p, int L, int R, int i, int j) {
        if (i > R || j < L) return {0, 0};
        if (i <= L && R <= j) return {value[p], sum[p]};
        pll out = combine(query(left(p), L, (L + R) / 2, i, j),
                          max((R + L) / 2 - max(L, i) + 1, 0),
                          query(right(p), (L + R) / 2 + 1, R, i, j));
        return out;
    }
    pll update(int p, int L, int R, int i, int val) {
        if (i > R || i < L) return {value[p], sum[p]};
        if (i == L && i == R) return {value[p] = val, sum[p] = val};
        pll out = combine(update(left(p), L, (L + R) / 2, i, val),
                          (R + L) / 2 - L + 1,
                          update(right(p), (L + R) / 2 + 1, R, i, val));
        return {value[p] = out.fi, sum[p] = out.se};
    }

   public:
    SegmentTree(int n) : n(n), value(n * 4, 0), sum(n * 4, 0) {
        build(1, 0, n - 1);
    }
    ll query(int i, int j) { return query(1, 0, n - 1, i, j).fi; }
    void update(int i, int val) {
        update(1, 0, n - 1, i, val);
        a[i] = val;
    }
    int size() { return n; }
};

void solve() {
    int n, q;
    cin >> n >> q;
    a.clear();
    a.assign(n, 0);
    F0R (i, n)
        cin >> a[i];
    SegmentTree st(n);
    ll ans = 0;
    F0R (i, q) {
        char type;
        cin >> type;
        if (type == 'U') {
            int x, v;
            cin >> x >> v;
            --x;
            st.update(x, v);
        } else {
            int r, l;
            cin >> r >> l;
            --r;
            --l;
            ll result = st.query(r, l);
            ans += result;
        }
    }
    cout << ans << endl;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int tt;
    cin >> tt;
    FOR (t, 1, tt + 1) {
        cout << "Case #" << t << ": ";
        solve();
    }

    return 0;
}
