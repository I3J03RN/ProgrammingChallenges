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

int N;

ii fromIndex(int index) { return mp(index / N, index % N); }
bool inBound(int r, int c) { return r >= 0 && r < N && c >= 0 && c < N; }

array<int, 4> dr{0, 0, 1, -1};
array<int, 4> dc{1, -1, 0, 0};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> N;
    vvi there(N, vi(N, 1)), hs(N, vi(N));

    FOR (i, 1, (N + 1) / 2) {
        FOR (c, i, N - i) {
            hs[i][c] = i;
            hs[N - 1 - i][c] = i;
        }
        FOR (r, i + 1, N - 1 - i) {
            hs[r][i] = i;
            hs[r][N - 1 - i] = i;
        }
    }
    F0R (r, N) {
        F0R (c, N) { dout << setw(3) << hs[r][c] << ' '; }
        dout << endl;
    }
    ll ans = 0;
    F0R (_, N * N) {
        dout << "hs:" << endl;
        for (auto& v : hs) {
            for (int i : v) dout << setw(3) << i;
            dout << endl;
        }

        int p;
        cin >> p;
        auto [pr, pc] = fromIndex(p - 1);
        there[pr][pc] = 0;
        ans += hs[pr][pc];

        dout << dvar(ans) << endl;
        queue<ii> q;
        q.emplace(pr, pc);
        while (!q.empty()) {
            auto [r, c] = q.ft;
            q.pop();
            F0R (i, 4) {
                int rr = r + dr[i], cc = c + dc[i];
                if (inBound(rr, cc) &&
                    ckmin(hs[rr][cc], hs[r][c] + there[r][c]))
                    q.emplace(rr, cc);
            }
        }
    }
    cout << ans << endl;

    return 0;
}
