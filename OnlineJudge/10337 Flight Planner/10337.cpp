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

int winds[10][1000];
int mem[10][1100];

const int INF = 10000000;

int getWind(int r, int c) {
    if (r < 0 || r >= 10) return 0;
    return winds[r][c];
}

int printV(int r, int c, int v) {
    // printf("%d, %d: %d\n", r, c, v);
    return v;
}

int solve(int r, int c) {
    // printf("%d, %d\n", r, c);
    if (r < 0 || r >= 10) return printV(r, c, INF);
    if (mem[r][c] != -1) return printV(r, c, mem[r][c]);
    return printV(
        r, c,
        mem[r][c] = min(20 + solve(r + 1, c - 1) - getWind(r + 1, c - 1),
                        min(30 + solve(r, c - 1) - getWind(r, c - 1),
                            60 + solve(r - 1, c - 1) - getWind(r - 1, c - 1))));
}

int main() {
    int cases;
    scanf("%d", &cases);
    mem[0][0] = 0;
    for (int r = 1; r < 10; ++r) mem[r][0] = INF;
    while (cases--) {
        int dist;
        scanf("%d", &dist);
        dist /= 100;
        for (int r = 0; r < 10; ++r)
            for (int c = 1; c <= dist; ++c) mem[r][c] = -1;

        for (int r = 0; r < 10; ++r)
            for (int c = 0; c < dist; ++c) scanf("%d", &winds[9 - r][c]);

        solve(0, dist);
        printf("%d\n\n", mem[0][dist]);
    }
}
