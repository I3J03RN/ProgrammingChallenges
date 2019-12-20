#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
typedef vector<vi> vvi;
typedef vector<vii> vvii;
#define FOR(a, b, c) for (auto(a) = (b); (a) < (c); ++(a))
#define FORI(a, b) for (auto(a) = (b).begin(); (a) != (b).end(); ++(a))

const int maxSize = (1 << 26) + 100;

bitset<maxSize> t;
bitset<maxSize> f;

char buffer[100];

bool solve(int i) {
    // cout << bitset<30>(i) << endl;
    if (t[i]) return true;
    if (f[i]) return false;

    int start = 25;
    while (!((1 << (start + 1)) & i)) start--;

    for (int j = start; j >= 0; j--)
        if ((1 << j) & i) {
            if (j == start) {
                if (solve(i & ~(1 << (j + 1)))) return t[i] = true;
            } else if (j == 0) {
                if (solve(i >> 1)) return t[i] = true;
            } else {
                int end = i & ((1 << (j - 1)) - 1);
                int starti = (i & ~((1 << (j + 2)) - 1)) >> 2;
                if (solve(starti | (1 << (j - 1)) | end)) return t[i] = true;
            }
        }

    f[i] = true;
    return false;
}

int encode(string s) {
    int out = 1;
    char last = '.';
    for (; !s.empty(); s = s.substr(1)) {
        if (last == s.front())
            out |= 1;
        else {
            last = s.front();
            out <<= 1;
        }
    }
    return out;
}

int main() {
    t[1] = true;
    int cases;
    scanf("%d", &cases);
    while (cases--) {
        scanf(" %30s", buffer);
        printf("%c\n", solve(encode(buffer)) ? '1' : '0');
        // cout << buffer << ": " << bitset<30>(encode(buffer)) << ", "
        //      << encode(buffer) << "\n";
    }
}
