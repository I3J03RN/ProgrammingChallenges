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
#define ge(a, b) get<(b)>((a))
#define SZ(x) (x).size()
#define ft front()
#define bk back()
#define endl '\n'
#define FOR(a, b, c) for (auto(a) = (b); (a) < (c); ++(a))
#define ROF(a, b, c) for (auto(a) = (b); (a) > (c); --(a))
#define F0R(a, b) FOR ((a), 0, (b))
#define R0F(a, b) ROF ((a), (b), -1)
#define CEIL(a, b) ((a) + (b)-1) / (b)
#define SET(a, b) memset((a), (b), sizeof(a))
#ifndef DEBUG
#define DEBUG 0
#endif
#define dout \
    if (DEBUG) std::cerr
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
    cout.tie(0);

    int n;
    string s;
    cin >> n >> s;
    vi sR(n + 1, 0), sG(n + 1, 0), sB(n + 1, 0);
    R0F (i, n - 1) {
        sR[i] = sR[i + 1] + (s[i] == 'R');
        sG[i] = sG[i + 1] + (s[i] == 'G');
        sB[i] = sB[i + 1] + (s[i] == 'B');
    }
    ll sum = 0;
    F0R (m, n) {
        F0R (f, m) {
            if (s[f] == s[m]) continue;
            char l = '?';
            for (char c : {'R', 'G', 'B'}) {
                if (c != s[f] && c != s[m]) {
                    l = c;
                    break;
                }
            }
            dout << "  " << f << ": " << l << endl;
            auto suf = ref(sR);
            if (l == 'G') suf = ref(sG);
            if (l == 'B') suf = ref(sB);
            assert(l != '?');
            sum += suf.get()[m + 1];
            if (m + (m - f) < n) sum -= s[m + (m - f)] == l;
        }
    }
    cout << sum << endl;

    return 0;
}
