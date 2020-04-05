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

void kmpPreprocess(const string& s, vi& back) {
    back.assign(SZ(s), 0);
    for (int i = 0, j = -1; i < SZ(s); ++i, ++j) {
        back[i] = j;
        while (j >= 0 && s[i] != s[j]) j = back[j];
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int tcs;
    cin >> tcs;
    while (tcs--) {
        string s;
        cin >> s;
        int l = 0, r = SZ(s) - 1;
        while (l <= r && s[l] == s[r]) {
            ++l;
            --r;
        }

        if (l > r) {
            cout << s << endl;
            continue;
        }
        string start = s.substr(0, l), end = s.substr(r + 1),
               text = s.substr(l, r - l + 1);

        string pattern(RALL(text));
        vi back;
        kmpPreprocess(pattern, back);

        int i = 0, j = 0;
        for (; i + j < SZ(text); ++i, ++j)
            while (j >= 0 && text[i] != pattern[j]) j = back[j];

        string s1(text.begin() + i - j, text.end());

        swap(text, pattern);
        back.clear();
        kmpPreprocess(pattern, back);

        i = 0, j = 0;
        for (; i + j < SZ(text); i++, j++)
            while (j >= 0 && text[i] != pattern[j]) j = back[j];

        string s2(text.begin() + i - j, text.end());

        cout << start << (SZ(s1) > SZ(s2) ? s1 : s2) << end << endl;
    }

    return 0;
}
