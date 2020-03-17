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

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    string s;
    cin >> s;

    vvi remove;
    while (true) {
        int l = 0, r = SZ(s) - 1;
        vi starts, ends;
        while (l < r) {
            if (s[l] == '(' && s[r] == ')') {
                starts.pb(l);
                ends.pb(r);
                l++;
                r--;
            } else {
                if (s[l] != '(') l++;
                if (s[r] != ')') r--;
            }
        }
        starts.insert(starts.end(), RALL(ends));
        if (starts.empty()) break;
        string newS = "";
        starts.pb(100000);
        int c = 0;
        F0R (i, SZ(s)) {
            if (i == starts[c])
                c++;
            else
                newS += s[i];
        }
        swap(s, newS);
        starts.pop_back();
        remove.pb(starts);
    }
    cout << SZ(remove) << endl;
    for (auto& v : remove) {
        cout << SZ(v) << endl;
        for (int i : v) cout << i + 1 << ' ';
        cout << endl;
    }

    return 0;
}
