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

void solve() {
    int n;
    cin >> n;
    vector<string> v(n);
    F0R (i, n)
        cin >> v[i];
    string out = "";
    vector<string> pre(n), suf(n);
    F0R (i, n) {
        string word = "";
        bool preFound = 0;
        for (char c : v[i]) {
            if (c == '*') {
                if (preFound)
                    out += word;
                else
                    pre[i] = word;
                word.clear();
                preFound = true;
            } else {
                word += c;
            }
        }
        suf[i] = word;
    }
    sort(ALL(pre), [](string& a, string& b) { return SZ(a) < SZ(b); });
    sort(ALL(suf), [](string& a, string& b) { return SZ(a) < SZ(b); });
    bool ok = true;
    F0R (i, n - 1) {
        F0R (j, SZ(pre[i]))
            if (pre.bk[j] != pre[i][j]) ok = false;
    }
    F0R (i, n - 1) {
        F0R (j, SZ(suf[i]))
            if (suf.bk[SZ(suf.bk) - 1 - j] != suf[i][SZ(suf[i]) - 1 - j])
                ok = false;
    }
    if (ok)
        cout << pre.bk << out << suf.bk << endl;
    else
        cout << '*' << endl;
}

int main() {
    ios_base::sync_with_stdio(0);
    cout.tie(0);

    int tcs;
    cin >> tcs;
    FOR (tc, 1, tcs + 1) {
        cout << "Case #" << tc << ": ";
        solve();
    }

    return 0;
}
