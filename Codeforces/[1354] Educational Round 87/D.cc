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

class FenwickTree {
   public:
    vi A;
    int n;
    int inline LSOne(int i) { return i & (-i); }
    int query(int i) {
        int sum = 0;
        for (; i; i -= LSOne(i)) sum += A[i];
        return sum;
    }

    FenwickTree(int n) : A(n + 1, 0), n(n) {}
    void adjust(int i, int adjustBy) {
        for (; i <= n; i += LSOne(i)) A[i] += adjustBy;
    }
    int query(int i, int j) { return query(j) - query(i - 1); }
    // lb assumes query(i, i) >= 0 forall i in [1, n]
    // returns min p >= 1, so that [1, p] >= sum
    // if [1, n] < sum, return n + 1
    int lb(int sum) {
        int pos = 0;
        for (int pw = 1 << 25; pw; pw >>= 1)
            if (pos + pw <= n && sum > A[pos | pw]) sum -= A[pos |= pw];
        if (sum) ++pos;
        assert(pos > 0);
        return pos;
    }
};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, q;
    cin >> n >> q;

    FenwickTree ftree(n);
    F0R (i, n) {
        int a;
        cin >> a;
        ftree.adjust(a, 1);
    }
    F0R (i, q) {
        int a;
        cin >> a;
        if (a >= 1)
            ftree.adjust(a, 1);
        else
            ftree.adjust(max(1, ftree.lb(abs(a))), -1);
    }
    FOR (i, 1, ftree.n + 1) {
        if (ftree.query(i)) {
            cout << i << endl;
            return 0;
        }
    }
    cout << 0 << endl;

    return 0;
}
