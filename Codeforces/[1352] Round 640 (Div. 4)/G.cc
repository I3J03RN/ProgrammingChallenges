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

array<int, 4> sol4 = {1, 3, 0, 2};
array<int, 5> sol5 = {1, 4, 2, 0, 3};
array<int, 6> sol6 = {1, 3, 5, 2, 0, 4};
array<int, 7> sol7 = {1, 3, 6, 4, 0, 2, 5};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int tt;
    cin >> tt;
    while (tt--) {
        int n;
        cin >> n;
        if (n <= 3) {
            cout << -1 << endl;
            continue;
        }
        int pos = 1;
        vi out;
        while (pos < n) {
            if (n - pos + 1 == 7) {
                for (int i : sol7) out.pb(pos + i);
                pos += 7;
            } else if (n - pos + 1 == 6) {
                for (int i : sol6) out.pb(pos + i);
                pos += 6;
            } else if (n - pos + 1 == 5) {
                for (int i : sol5) out.pb(pos + i);
                pos += 5;
            } else {
                for (int i : sol4) out.pb(pos + i);
                pos += 4;
            }
        }
        for (int i : out) cout << i << ' ';
        cout << endl;
    }

    return 0;
}
