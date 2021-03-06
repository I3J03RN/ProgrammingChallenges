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

const int border = 1000000;

int steps[border];

int calc(int n) {
    // printf("%d\n", n);
    if (n >= border) return calc(n & 1 ? 3 * n + 1 : n >> 1) + 1;
    if (steps[n] != -1) return steps[n];
    return steps[n] = calc(n & 1 ? 3 * n + 1 : n >> 1) + 1;
}

int main() {
    memset(steps, -1, sizeof(steps));
    steps[0] = 1;
    steps[1] = 1;
    int i, j;
    while (scanf("%d %d", &i, &j) != EOF) {
        int m = 0;
        for (int n = min(i, j); n <= max(j, i); ++n) m = max(m, calc(n));
        printf("%d %d %d\n", i, j, m);
    }
}
