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

bool asteroids[100][100] = {{0}};
char buffer[110];

int h = 0, w;

int main() {
    for (; fgets(buffer, 100, stdin); ++h) {
        w = strlen(buffer) - 1;
        for (int i = 0; i < w; ++i) asteroids[h][i] = (buffer[i] == '#');
    }
    printf("height: %d, width: %d\n", h, w);
    for (int r = 0; r < h; ++r) {
        for (int c = 0; c < w; ++c) printf("%c", asteroids[r][c] ? '#' : '.');
        printf("\n");
    }
    int best = 0;
    for (int r = 0; r < h; ++r)
        for (int c = 0; c < w; ++c) {
            int count = 0;
            if (!asteroids[r][c]) continue;
            for (int rr = 0; rr < h; ++rr)
                for (int cc = 0; cc < w; ++cc) {
                    if ((rr == r && cc == c) || !asteroids[rr][cc]) continue;
                    int g = gcd<int, int>(abs(cc - c), abs(rr - r));
                    int stepr = (rr - r) / g;
                    int stepc = (cc - c) / g;
                    bool fine = true;
                    for (int tr = r + stepr, tc = c + stepc;
                         tr != rr || tc != cc; tr += stepr, tc += stepc)
                        if (asteroids[tr][tc]) {
                            fine = false;
                            break;
                        }
                    if (fine) {
                        printf("(%d, %d) -- (%d, %d), %d %d\n", r, c, rr, cc,
                               stepr, stepc);
                        count++;
                    }
                }
            printf("count %d\n", count);
            best = max(best, count);
        }
    printf("best: %d\n", best);
}
